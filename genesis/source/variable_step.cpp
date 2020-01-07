// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "variable_step.hpp"

#include "recipe_callback.hpp"


namespace sx
{


namespace genesis
{


variable_step::variable_step( const std::string& _variable_name ) :
	recipe_step(),
	variable_name_( _variable_name )
{
	// Nothing to do...
}


variable_step::~variable_step() noexcept
{
	// Nothing to do...
}


void variable_step::create( recipe_callback& _recipe_callback, std::stringstream& _ostream, [[maybe_unused]] const int _indent )
{
	_ostream << _recipe_callback.get_variable_content( variable_name_ );
}


}


}
