// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef RECIPE_BLOCK_A5AF03FF_E23E_4887_A4C8_44C6E8605983
#define RECIPE_BLOCK_A5AF03FF_E23E_4887_A4C8_44C6E8605983


#include <vector>

#include "recipe_step.hpp"


namespace sx
{


namespace genesis
{

//!\class recipe_block
//!\brief Class that represents a recipe block. This block can have children.
class recipe_block : public recipe_step
{
public:
	//!\brief Constructor
	explicit recipe_block();
	virtual ~recipe_block() noexcept override;
	SXE_NO_COPY( recipe_block )

	//!\brief Add a child to the list of children.
	//!\param _child New child
	virtual void add_child( std::unique_ptr<recipe_step>&& _child );


protected:
	//!\brief Create the output for a step.
	//!\param _recipe_callback Generator callback
	//!\param _ostream Stream to which the generator writes.
	//!\param _indent indent of the block.
	virtual void create_children( recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent );


private:
	std::vector< std::unique_ptr<recipe_step> > child_recipes_;
};


}


}


#endif
