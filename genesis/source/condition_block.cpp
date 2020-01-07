// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "condition_block.hpp"

#include "essentials/exception.hpp"

#include "recipe_callback.hpp"


namespace sx
{


namespace genesis
{


condition_block::condition_block( const std::string& _condition_name, const condition_modifier& _modifier ) :
	recipe_block(),
	condition_name_( _condition_name ),
	modifier_( _modifier )
{
	// Nothing to do...
}


condition_block::~condition_block() noexcept
{
	// Nothing to do...
}


void condition_block::create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	_recipe_callback.condition_begin( condition_name_ );
	bool result = _recipe_callback.check_condition( condition_name_ );
	apply_modifier( result );
	if( result )
	{
		create_children( _recipe_callback, _ostream, _indent );
	}
	_recipe_callback.condition_end( condition_name_ );
}


void condition_block::apply_modifier( bool& _result ) const
{
	switch( modifier_ )
	{
	case sx::genesis::condition_modifier::NOT:
		_result = !_result;
		break;

	case sx::genesis::condition_modifier::NONE:
		// Nothing to do...
		break;

	default:
		sxe::exception( "Incompatible value for condition modifier!" );
		break;
	}
}


}


}
