// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef RECIPE_STEP_1A42F342_F0C6_49C9_8FC3_0BAEDFBD05AE
#define RECIPE_STEP_1A42F342_F0C6_49C9_8FC3_0BAEDFBD05AE


#include <sstream>

#include "essentials/compatibility/compatibility.hpp"
#include "essentials/non_copyable.hpp"


namespace sx
{


namespace genesis
{


class recipe_callback;


//!\interface recipe_step
//!\brief A step of a recipe.
class recipe_step
{
public:
	//!\brief Constructor
	recipe_step()
	{
		// Nothing to do...
	}


	virtual ~recipe_step() noexcept
	{
		// Nothing to do...
	}


	// cppcheck-suppress unknownMacro
	SXE_NO_COPY( recipe_step )

	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent Indent of the step.
	virtual void create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent ) = 0;
};


}


}

#endif
