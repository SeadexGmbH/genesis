// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "file_writer.hpp"

#include <fstream>

#include "genesis_exception.hpp"
#include "messages.hpp"


namespace sx
{


namespace genesis
{


// cppcheck-suppress unusedFunction
void write( const std::string& _file_path, const std::ostream& _output_stream )
{
	std::ofstream target_file( _file_path, std::ios_base::out | std::ios_base::binary );

	if( target_file.is_open() )
	{
		target_file << _output_stream.rdbuf();
		target_file.close();
	}
	else
	{
		throw genesis_exception( ERROR_WRITE_FILE, _file_path );
	}
}


}


}
