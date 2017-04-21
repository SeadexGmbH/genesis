//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                  //
// This file is part of the Seadex genesis library (http://genesis.seadex.de).                      //
// Copyright( C ) 2017 Seadex GmbH                                                                  //
// Licensing information is available in the folder "license" which is part of this distribution.   //
// The same information is available on the www @ http://genesis.seadex.de/License.html.            //
//                                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONDITION_MODIFIER_5286AF53_4751_4FDE_B4C9_E097AC8FB331
#define CONDITION_MODIFIER_5286AF53_4751_4FDE_B4C9_E097AC8FB331


#include <string>


namespace sx
{


namespace genesis
{


//!\enum condition_modifier
//!\brief Modifier for conditions. E.g. negate the result of a check.
enum class condition_modifier
{
	NONE = 0, NOT = 1
};


//!\fn
//!\brief Get the condition modifier value from a string.
//!\param _condition_modifier Modifier as a string, generally read from template files.
//!\return Condition modifier enum value corresponding to the given value.
condition_modifier get_condition_modifier_from_string( const std::string& _condition_modifier );


}


}


#endif
