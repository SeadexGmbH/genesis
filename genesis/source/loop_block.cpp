// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "loop_block.hpp"

#include "recipe_callback.hpp"


namespace sx
{


namespace genesis
{


loop_block::loop_block( const std::string& _loop_name ) :
	recipe_block(),
	loop_name_( _loop_name )
{
	// Nothing to do...
}


loop_block::~loop_block() noexcept
{
	// Nothing to do...
}


void loop_block::create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	_recipe_callback.before_loop( loop_name_ );
			
	while( _recipe_callback.check_loop_condition( loop_name_ ) )
	{
		_recipe_callback.before_loop_iteration( loop_name_ );
		create_children( _recipe_callback, _ostream, _indent );
		_recipe_callback.after_loop_iteration( loop_name_ );
	}
	_recipe_callback.after_loop( loop_name_ );
}


}


}
