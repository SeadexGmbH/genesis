// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "recipe_block.hpp"


namespace sx
{


namespace genesis
{


recipe_block::recipe_block() :
	recipe_step(),
	child_recipes_()
{
	// Nothing to do...
}


recipe_block::~recipe_block() noexcept
{
	// Nothing to do...
}


void recipe_block::create_children( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	for( std::unique_ptr<recipe_step>& child :  child_recipes_ )
	{
		child->create( _recipe_callback, _ostream, _indent );
	}
}


void recipe_block::add_child( std::unique_ptr<recipe_step>&& _child )
{
	child_recipes_.push_back( std::move( _child ) );
}


}


}
