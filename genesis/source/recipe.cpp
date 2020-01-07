// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "recipe.hpp"

#include "file_writer.hpp"
#include "genesis_exception.hpp"


namespace sx
{


namespace genesis
{


recipe::recipe( const std::string& _template_name, recipe_callback& _recipe_callback, 
	const std::string& _templates_path ) :
		template_block( _template_name, _templates_path, 0 ),
		recipe_callback_( _recipe_callback ),
		stream_()
{
	// Nothing to do...
}


recipe::~recipe() noexcept
{
	// Nothing to do...
}


void recipe::generate()
{
	create_impl( recipe_callback_ );
}


void recipe::write_to_file( const std::string& _file_path ) const
{
	write( _file_path, stream_ );
}


void recipe::create_impl( recipe_callback& _recipe_callback )
{
	template_block::create( _recipe_callback, stream_, get_indent() );
}

std::string recipe::get_content() const {
	return(stream_.str());
}


}


}
