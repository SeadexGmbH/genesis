// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef RECIPE_20F2FCF1_99D0_4CC6_9E59_3E9BE7C1A2A6
#define RECIPE_20F2FCF1_99D0_4CC6_9E59_3E9BE7C1A2A6


#include "template_block.hpp"


namespace sx
{


namespace genesis
{


class recipe_step;

//!\class recipe
//!\brief Class for generating code from the given template and using the given callback. It can write the generated code 
//! to the given file.
class recipe : public template_block
{
public:
	//!\brief Constructor
	//!\param _template_name Name of the file containing the used template.
	//!\param _recipe_callback Generator callback
	//!\param _templates_path Path to the templates folder.
	explicit recipe( const std::string& _template_name, recipe_callback& _recipe_callback, 
		const std::string& _templates_path );
	virtual ~recipe() noexcept override;
	SXE_NO_COPY( recipe )

	//!\brief Generates the code in an internal stream.
	void generate();

	//!\brief Write the generated code to the file with the given name.
	//!\param _file_path Path of the file to which the generated code will be written.
	void write_to_file( const std::string& _file_path ) const;

	std::string get_content() const;


private:
	void create_impl( recipe_callback& _recipe_callback );

	recipe_callback& recipe_callback_;
	std::stringstream stream_;
};


}


}


#endif
