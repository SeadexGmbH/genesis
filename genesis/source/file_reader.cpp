// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "file_reader.hpp"

#include <sstream>
#include <fstream>


namespace sx
{

namespace genesis
{


bool read( const std::string& _file_path, std::string& _content )
{
	bool read = false;
	std::ostringstream outputString;
	std::ifstream inputFile( _file_path.c_str(), std::ios::in );
	if( inputFile )
	{
		outputString << inputFile.rdbuf();
		inputFile.close();
		read = true;
	}
	_content = outputString.str();
	return ( read );
}


}


}
