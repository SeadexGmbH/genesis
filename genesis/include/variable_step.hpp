// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef VARIABLE_STEP_11B39100_54E6_40E4_85FC_0A642202937C
#define VARIABLE_STEP_11B39100_54E6_40E4_85FC_0A642202937C


#include "recipe_step.hpp"


namespace sx
{


namespace genesis
{


//!\class variable_step
//!\brief Class representing a variable step of the recipe.
class variable_step final 
	: public recipe_step
{
public:
	//!\brief Constructor
	//!\param _variable_name Name of the variable represented by the variable_step.
	explicit variable_step( const std::string& _variable_name );
	virtual ~variable_step() noexcept override;
	SXE_NO_COPY( variable_step )

	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent Indent of the block.
	virtual void create( recipe_callback& _recipe_callback, std::stringstream& _ostream, [[maybe_unused]] 
		const int _indent ) override;


private:
	const std::string variable_name_;
};


}


}


#endif
