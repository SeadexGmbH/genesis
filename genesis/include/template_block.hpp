// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef TEMPLATE_BLOCK_43849414_0A6E_429C_9D51_FB0562A58B05
#define TEMPLATE_BLOCK_43849414_0A6E_429C_9D51_FB0562A58B05


#include <stack>

#include "recipe_block.hpp"


namespace sx
{


namespace genesis
{


class text_step;
class variable_step;
class loop_block;
class condition_block;


//!\class template_block
//!\brief Class representing a recipe block created from a template file.
class template_block 
	: public recipe_block
{
public:
	//!\brief Constructor. Get the template file name and the path to the template directory.
	//!\param _template_name Name of the template file.
	//!\param _template_path Path to templates directory
	//!\param _indent Indent of the block.
	explicit template_block( const std::string& _template_name, const std::string& _template_path,
			const int _indent );
	virtual ~template_block() noexcept override;
	SXE_NO_COPY( template_block )

	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent Indent of the block.
	virtual void create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent ) override;


protected:
	int get_indent() const;


private:
	void parse( std::string& _file_buffer );
	void get_text( std::string &_file_buffer );
	std::string get_keyword( std::string& _file_buffer );
	void get_variable( std::string &_file_buffer );
	void get_loop( std::string &_file_buffer );
	void get_if( std::string &_file_buffer );
	void get_switch( std::string& _file_buffer );
	void get_switch_case( std::string& _file_buffer );
	void get_switch_default( std::string& _file_buffer );
	void get_template( std::string &_file_buffer );
	const std::string get_last_to_be_closed() const;			
	static std::string read_template_file( const std::string& _file_buffer, const std::string& _templates_path );
	void close_loop( std::string& _file_buffer );
	void close_condition( std::string& _file_buffer );
	void close_switch( std::string& _file_buffer );
	void close_switch_case( std::string& _file_buffer );
	void close_switch_default( std::string& _file_buffer );
	bool is_any_recipe_open() const;
	std::vector<std::string> get_parameters( std::string& _file_buffer ) const;
	void final_check() const;
	static void remove_newline( std::string& _file_buffer );

	template<typename T>
	void add_child_to_recipe( std::unique_ptr<T> _child )
	{
		if( opened_recipes_.empty() )
		{
			add_child( std::move( _child ) );
		}
		else
		{
			opened_recipes_.top()->add_child( std::move( _child ) );
		}
	}


	std::stack<recipe_block*> opened_recipes_;
	std::vector<std::string> keywords_;
	std::string template_to_parse_;
	const std::string template_path_;
	const std::string template_file_;
	const int indent_;
};


}


}


#endif
