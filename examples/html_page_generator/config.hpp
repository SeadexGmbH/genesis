// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).


#ifndef CONFIG_F0DF6484_1AB7_48AC_9471_42C853B24430
#define CONFIG_F0DF6484_1AB7_48AC_9471_42C853B24430


#include "country.hpp"


namespace examples
{


struct config
{
	config();

	std::string template_path_;
	std::string source_template_file_;
	std::string output_file_;
	std::vector<country> countries_;
};


}


#endif
