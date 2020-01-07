// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "condition_modifier.hpp"

#include <algorithm>

#include "essentials/conversion.hpp"

#include "grammar.hpp"
#include "genesis_exception.hpp"


namespace sx
{


namespace genesis
{


// cppcheck-suppress unusedFunction
condition_modifier get_condition_modifier_from_string( const std::string& _condition_modifier )
{
	const std::string condition_modifier_caps = sxe::to_upper( _condition_modifier );

	condition_modifier modifier( condition_modifier::NONE );
	if( condition_modifier_caps == condition_modifier_NOT )
	{
		modifier = condition_modifier::NOT;
	}
	else if( condition_modifier_caps == condition_modifier_NONE )
	{
		modifier = condition_modifier::NONE;
	}
	else
	{
		throw genesis_exception( "Invalid condition modifier!" );
	}
	return ( modifier );
}


}


}
