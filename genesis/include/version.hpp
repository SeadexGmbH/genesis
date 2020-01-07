// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).


#ifndef VERSION_11BB60D2_9C1A_4102_BBCC_0486F61F9C1C
#define VERSION_11BB60D2_9C1A_4102_BBCC_0486F61F9C1C


#include "essentials/compatibility/compatibility.hpp"


namespace sx
{


namespace genesis
{


namespace version
{


void log_version();


std::uint16_t get_major_version();
std::uint16_t get_minor_version();
std::uint16_t get_patch_version();


}


}


}


#endif
