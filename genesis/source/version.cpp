// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).


#include <iostream>

#include "fmt/format.h"

#include "version.hpp"


namespace sx
{


namespace genesis
{


namespace version
{


namespace
{


const std::uint16_t VERSION_MAJOR( 2 );
const std::uint16_t VERSION_MINOR( 0 );
const std::uint16_t VERSION_PATCH( 0 );


}


// cppcheck-suppress unusedFunction
void log_version()
{
	std::cout << fmt::format( "genesis library version {}.{}.{}.", get_major_version(),
		get_minor_version(), get_patch_version() ) << std::endl;
}


std::uint16_t get_major_version()
{
	return( VERSION_MAJOR );
}


std::uint16_t get_minor_version()
{
	return( VERSION_MINOR );
}


std::uint16_t get_patch_version()
{
	return( VERSION_PATCH );
}


}


}


}
