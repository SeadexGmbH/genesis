// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef LOOP_BLOCK_08F296C5_8660_453B_9AE3_903E1AEE52D9
#define LOOP_BLOCK_08F296C5_8660_453B_9AE3_903E1AEE52D9


#include "recipe_block.hpp"


namespace sx
{


namespace genesis
{


//!\class loop_block
//!\brief Class representing a loop. This block can have children.
class loop_block final
	: public recipe_block
{
public:
	//!\brief Constructor
	//!\param _loop_name Name of the loop block.
	explicit loop_block( const std::string& _loop_name);
	virtual ~loop_block() noexcept override;
	SXE_NO_COPY( loop_block )

	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent indent of the block.
	virtual void create( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent ) override;


private:
	const std::string loop_name_;
};


}


}


#endif
