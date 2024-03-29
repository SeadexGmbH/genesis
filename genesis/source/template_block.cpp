// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "template_block.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "essentials/assert.hpp"
#include "essentials/conversion.hpp"

#include "genesis_exception.hpp"
#include "file_reader.hpp"
#include "text_step.hpp"
#include "variable_step.hpp"
#include "loop_block.hpp"
#include "switch_block.hpp"
#include "condition_block.hpp"
#include "grammar.hpp"


namespace sx
{


namespace genesis
{


template_block::template_block( const std::string& _template_name, const std::string& _template_path,
		const int _indent ) :
	recipe_block(),
	opened_recipes_(),
	keywords_(),
	template_to_parse_( read_template_file( _template_name, _template_path ) ),
	template_path_( _template_path ),
	template_file_( _template_name ),
	indent_( _indent )
{
	// Nothing to do...
}


template_block::~template_block() noexcept
{
	// Nothing to do...
}


void template_block::create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	parse( template_to_parse_ );
	final_check();
	create_children( _recipe_callback, _ostream, get_indent() + _indent );
}


int template_block::get_indent() const {
	return( indent_ );
}


void template_block::parse( std::string& _file_buffer )
{
	while( !_file_buffer.empty() )
	{
		get_text( _file_buffer );
		if( !_file_buffer.empty() )
		{
			const std::string command = get_keyword( _file_buffer );
			if( command == VARIABLE_COMMAND )
			{
				get_variable( _file_buffer );
			}
			else if( command == TEMPLATE_COMMAND )
			{
				get_template( _file_buffer );
			}
			else if( command == LOOP_START_COMMAND )
			{
				get_loop( _file_buffer );
			}
			else if( command == IF_START_COMMAND )
			{
				get_if( _file_buffer );
			}
			else if( command == SWITCH_START_COMMAND )
			{
				get_switch( _file_buffer );
			}
			else if( command == SWITCH_CASE_START_COMMAND )
			{
				get_switch_case( _file_buffer );
			}
			else if( command == SWITCH_DEFAULT_START_COMMAND )
			{
				get_switch_default( _file_buffer );
			}
			else if( command == LOOP_END_COMMAND )
			{
				close_loop( _file_buffer );
			}
			else if( command == IF_END_COMMAND )
			{
				close_condition( _file_buffer );
			}
			else if( command == SWITCH_END_COMMAND )
			{
				close_switch( _file_buffer );
			}
			else if( command == SWITCH_CASE_END_COMMAND )
			{
				close_switch_case( _file_buffer );
			}
			else if( command == SWITCH_DEFAULT_END_COMMAND )
			{
				close_switch_default( _file_buffer );
			}
			else
			{
				throw genesis_exception( "Unknown command '{}'! Check template file '{}'!", command, template_file_ );
			}
			remove_newline( _file_buffer );
		}
	}
}


void template_block::get_text( std::string &_file_buffer )
{
	std::stringstream buffer;
	bool more_text = true;
	while( more_text )
	{
		const std::size_t position = _file_buffer.find( DELIMITER_CHAR );
		if( position != std::string::npos )
		{
			buffer << _file_buffer.substr( 0, position );
			_file_buffer.erase( 0, position );
			[[maybe_unused]] const bool is_delimiter_char = _file_buffer[0] == DELIMITER_CHAR;
			SXE_ASSERT( is_delimiter_char, "First char in the buffer is not the delimiter char!" );
			if( _file_buffer.length() > 2 )
			{
				if( _file_buffer[1] == DELIMITER_CHAR )
				{
					buffer << DELIMITER_CHAR;
					_file_buffer.erase( 0, 2 );
				}
				else if( _file_buffer[1] == LINE_BREAK_CHAR )
				{
					buffer << '\n';
					_file_buffer.erase( 0, 2 );
					remove_newline(_file_buffer);
				}
				else
				{
					more_text = false;

					const std::string text = buffer.str();
					buffer.str( std::string() );
					add_child_to_recipe( sxe::make_unique<text_step>( text ) );
				}
			}
			else
			{
				if(_file_buffer.length() == 2)
				{
					if(_file_buffer[ 1 ] == DELIMITER_CHAR)
					{
						buffer << DELIMITER_CHAR;
						_file_buffer.erase( 0, 2 );
					}
					else if(_file_buffer[ 1 ] == LINE_BREAK_CHAR)
					{
						buffer << '\n';
						_file_buffer.erase( 0, 2 );
						remove_newline( _file_buffer );
					}
					else
					{
						throw genesis_exception( "File '{}' ends with a stray delimiter char followed by '{}'!", template_file_, _file_buffer[ 1 ] );
					}
				}
				else
				{
					throw genesis_exception( "File '{}' ends with a stray delimiter char!", template_file_ );
				}
			}
		}
		else
		{
			more_text = false;
			if( is_any_recipe_open() )
			{
				throw genesis_exception( "A condition/loop not closed in file '{}'!", template_file_ );
			}
			else
			{
				const std::string text = buffer.str() + _file_buffer;
				if(!text.empty())
				{
					auto new_text_step = sxe::make_unique<text_step>( text );
					add_child( std::move( new_text_step ) );
				}
				buffer.str( std::string() );
				_file_buffer.clear();
			}
		}
	}
}


std::string template_block::get_keyword( std::string& _file_buffer )
{
	std::size_t position;
	if( keywords_.empty() )
	{
		position = _file_buffer.find( OPEN_PARENTHESIS_CHAR );
	}
	else
	{
		if( _file_buffer.substr( 0, get_last_to_be_closed().length() ) == get_last_to_be_closed() )
		{
			position = get_last_to_be_closed().length();
		}
		else
		{
			position = _file_buffer.find( OPEN_PARENTHESIS_CHAR );
		}
	}

	std::string keyword = "";
	if( position != std::string::npos )
	{
		keyword = _file_buffer.substr( 0, position );
	}
	else
	{
		throw genesis_exception( "No command found!" );
	}
	return ( keyword );
}


void template_block::get_variable( std::string &_file_buffer )
{
	_file_buffer.erase( 0, VARIABLE_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.size() != 1 )
	{
		throw genesis_exception( "Variable command does not have exactly 1 parameter in file '{}'!", template_file_ );
	}
	else
	{
		add_child_to_recipe( sxe::make_unique<variable_step>( parameters[0] ) );
	}
}


void template_block::get_loop( std::string &_file_buffer )
{
	_file_buffer.erase( 0, LOOP_START_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.size() != 1 )
	{
		throw genesis_exception( "Loop command does not have exactly 1 parameter in file '{}'!", template_file_ );
	}
	else
	{
		auto new_loop_block = sxe::make_unique<loop_block>( parameters[0] );
		loop_block* new_loop_block_ptr = new_loop_block.get();
		add_child_to_recipe( std::move( new_loop_block ) );
		opened_recipes_.push( new_loop_block_ptr );
		keywords_.push_back( LOOP_END_COMMAND );
	}
}


void template_block::get_if( std::string &_file_buffer )
{
	keywords_.push_back( IF_END_COMMAND );
	_file_buffer.erase( 0, IF_START_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.size() != 1 && parameters.size() != 2 )
	{
		throw genesis_exception( "No sufficient parameters provided for 'if' command in file '{}'!", template_file_ );
	}
	else
	{
		std::unique_ptr<condition_block> new_condition_block;
		if( parameters.size() > 1 )
		{
			new_condition_block =
				sxe::make_unique<condition_block>( parameters[0], get_condition_modifier_from_string( parameters[1] ) );
		}
		else
		{
			new_condition_block =
				sxe::make_unique<condition_block>( parameters[0], condition_modifier::NONE );
		}
		condition_block* new_condition_block_ptr = new_condition_block.get();
		add_child_to_recipe( std::move( new_condition_block ) );
		opened_recipes_.push( new_condition_block_ptr );
	}
}


void template_block::get_switch( std::string& _file_buffer )
{
	_file_buffer.erase( 0, SWITCH_START_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.size() != 1 )
	{
		throw genesis_exception( "Switch command has not exactly 1 parameter in file '{}'!", template_file_ );
	}
	else
	{
		std::unique_ptr<switch_block> new_switch_block = sxe::make_unique<switch_block>( parameters[0] );
		switch_block* new_switch_block_ptr = new_switch_block.get();
		add_child_to_recipe( std::move( new_switch_block ) );
		opened_recipes_.push( new_switch_block_ptr );
		keywords_.push_back( SWITCH_END_COMMAND );
	}
}


void template_block::get_switch_case( std::string& _file_buffer )
{
	_file_buffer.erase( 0, SWITCH_CASE_START_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.size() != 1 )
	{
		throw genesis_exception( "Switch case command has not exactly 1 parameter in file '{}'!", template_file_ );
	}
	else
	{
		if( opened_recipes_.empty() )
		{
			throw genesis_exception( "There is no switch for the switch case in '{}'!", template_file_ );
		}
		else
		{
			switch_block* switch_ = dynamic_cast< switch_block* >( opened_recipes_.top() );
			if( switch_ )
			{
				int index = 0;
				sxe::string_to_integer( parameters[0].c_str(), index );
				switch_->set_case_index( index );
				keywords_.push_back( SWITCH_CASE_END_COMMAND );
			}
			else
			{
				throw genesis_exception( "There is no switch for the switch case in '{}'!", template_file_ );
			}
		}
	}
}


void template_block::get_switch_default( std::string& _file_buffer )
{
	_file_buffer.erase( 0, SWITCH_DEFAULT_START_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( !parameters.empty())
	{
		throw genesis_exception( "Switch default command must have no parameters in file '{}'!", template_file_ );
	}
	else
	{
		if( opened_recipes_.empty() )
		{
			throw genesis_exception( "There is no switch for the default case in '{}'!", template_file_ );
		}
		else
		{
			switch_block* switch_ = dynamic_cast< switch_block* >( opened_recipes_.top() );
			if( switch_ )
			{
				switch_->set_case_index( SWITCH_DEFAULT_INDEX_VALUE );
				keywords_.push_back( SWITCH_DEFAULT_END_COMMAND );
			}
			else
			{
				throw genesis_exception( "There is no switch for the switch default in '{}'!", template_file_ );
			}
		}
	}
}


void template_block::get_template( std::string &_file_buffer )
{
	_file_buffer.erase( 0, TEMPLATE_COMMAND.length() + SIZE_ONE );
	const std::vector<std::string> parameters = get_parameters( _file_buffer );
	if( parameters.empty() )
	{
		throw genesis_exception( "No sufficient parameters provided for 'template' command in file '{}'!", template_file_ );
	}
	else
	{
		const std::string template_name = parameters[0];
		int extra_indent = 0;
		if( parameters.size() > 1 )
		{
			if(!sxe::string_to_integer(parameters[1].c_str(), extra_indent))
			{
				throw genesis_exception( "Indent '{}' is no integer!", parameters[1] );
			}
		}
		add_child_to_recipe( sxe::make_unique<template_block>( template_name , template_path_, extra_indent ) );
	}
}


const std::string template_block::get_last_to_be_closed() const
{
	const std::string last_element = keywords_.back();
	return( last_element );
}


std::string template_block::read_template_file( const std::string& _template_name, const std::string& _templates_path )
{
	std::string template_file_as_string;
	read( _templates_path + "/" + _template_name, template_file_as_string );
	if( template_file_as_string.empty() )
	{
		// TODO
		std::cout << "Template file '" << _template_name << "' is empty!" << std::endl;
	}
	return( template_file_as_string );
}


void template_block::close_loop( std::string& _file_buffer )
{
	const std::size_t position = _file_buffer.find( LOOP_END_COMMAND );
	_file_buffer.erase( 0, position + LOOP_END_COMMAND.length() );
	keywords_.pop_back();
	opened_recipes_.pop();
}


void template_block::close_condition( std::string& _file_buffer )
{
	const std::size_t position = _file_buffer.find( IF_END_COMMAND );
	_file_buffer.erase( 0, position + IF_END_COMMAND.length() );
	keywords_.pop_back();
	opened_recipes_.pop();
}


void template_block::close_switch( std::string& _file_buffer )
{
	const std::size_t position = _file_buffer.find( SWITCH_END_COMMAND );
	_file_buffer.erase( 0, position + SWITCH_END_COMMAND.length() );
	keywords_.pop_back();
	opened_recipes_.pop();
}


void template_block::close_switch_case( std::string& _file_buffer )
{
	const std::size_t position = _file_buffer.find( SWITCH_CASE_END_COMMAND );
	_file_buffer.erase( 0, position + SWITCH_CASE_END_COMMAND.length() );
	keywords_.pop_back();	
}


void template_block::close_switch_default( std::string& _file_buffer )
{
	const std::size_t position = _file_buffer.find( SWITCH_DEFAULT_END_COMMAND );
	_file_buffer.erase( 0, position + SWITCH_DEFAULT_END_COMMAND.length() );
	keywords_.pop_back();
}
		

bool template_block::is_any_recipe_open() const
{
	return( !opened_recipes_.empty() );
}


std::vector<std::string> template_block::get_parameters( std::string& _file_buffer ) const
{
	std::vector<std::string> parameters;
	std::size_t stop_position = _file_buffer.find( CLOSE_PARENTHESIS_CHAR );
	std::string string_parameters = _file_buffer.substr( 0, stop_position );
	_file_buffer.erase( 0, stop_position + SIZE_ONE );

	string_parameters.erase( std::remove_if( string_parameters.begin(), string_parameters.end(), ::isspace ), string_parameters.end() );

	std::string step;
	std::istringstream stream( string_parameters );
	while( getline( stream, step, ',' ) )
	{
		parameters.push_back( step );
	}

	return( parameters );
}


void template_block::final_check() const
{
	SXE_ASSERT( template_to_parse_.empty(), "The file buffer was not completely parsed!" );

	if( !keywords_.empty() )
	{
		std::string command = keywords_.back();
		if( command == LOOP_END_COMMAND )
		{
			command = LOOP_START_COMMAND;
		}
		else if( command == IF_END_COMMAND )
		{
			command = IF_START_COMMAND;
		}
		else
		{
			genesis_exception( "Unknown command end: '{}'!", command );
		}

		genesis_exception( "Command '{}' does not have a close command in file '{}'!", command, template_file_ );
	}

	if( !opened_recipes_.empty() )
	{
		genesis_exception( "Internal error! Not all recipes were processed at the end of generation." );
	}
}

void template_block::remove_newline( std::string& _file_buffer )
{
	if( !_file_buffer.empty() && _file_buffer[0] == NEW_LINE_CHAR ) {
		_file_buffer.erase(0, 1);
	}
}

}

}
