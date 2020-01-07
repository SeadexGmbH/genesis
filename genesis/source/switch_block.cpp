// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "switch_block.hpp"

#include "recipe_callback.hpp"


namespace sx
{


namespace genesis
{


switch_block::switch_block( const std::string& _switch_name ) :
	recipe_block(),
	switch_name_( _switch_name ),
	current_case_index_(),
	switch_cases_(),
	default_()
{
	// Nothing to do...
}


switch_block::~switch_block() noexcept
{
	// Nothing to do...
}


void switch_block::create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	current_case_index_ = _recipe_callback.get_switch_case( switch_name_ );
	create_children( _recipe_callback, _ostream, _indent);
}


void switch_block::create_children( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	if( current_case_index_ >= 0 )
	{
		std::vector< std::unique_ptr<recipe_step> >& children_steps = switch_cases_[current_case_index_];
		for(std::unique_ptr<recipe_step>& child : children_steps )
		{
			child->create( _recipe_callback, _ostream, _indent );
		}
	}
	else
	{
		for( std::unique_ptr<recipe_step>& child : default_ )
		{
			child->create( _recipe_callback, _ostream, _indent );
		}
	}	
}


void switch_block::add_child( std::unique_ptr<recipe_step>&& _child )
{
	if( current_case_index_ >= 0 )
	{
		switch_cases_[current_case_index_].push_back( std::move( _child ) );
	}
	else
	{
		default_.push_back( std::move( _child ) );
	}
}


void switch_block::set_case_index( const int _index )
{
	current_case_index_ = _index;
}


}


}
