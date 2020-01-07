// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef TEXT_STEP_56DA4C34_9848_4123_AB65_1C9839E009A2
#define TEXT_STEP_56DA4C34_9848_4123_AB65_1C9839E009A2

#include <vector>

#include "recipe_step.hpp"


namespace sx
{


namespace genesis
{


//!\class test_step
//!\brief Class representing a text step of the recipe.
class text_step final 
	: public recipe_step
{
public:
	//!\brief Constructor
	//!\param _text Content of the text block.
	explicit text_step( const std::string& _text );
	virtual ~text_step() noexcept override;
	SXE_NO_COPY( text_step )

	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent Indent of the block.
	virtual void create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent ) override;


private:
	std::vector<std::string> split() const;
	static std::string create_indent( const int _indent );


	const std::string text_;
};


}


}


#endif
