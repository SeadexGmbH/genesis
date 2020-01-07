// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef COUNTRY_8520C99E_118A_4693_A3BB_D1268053EFEE
#define COUNTRY_8520C99E_118A_4693_A3BB_D1268053EFEE

#include <vector>

#include "city.hpp"


// DONE remove cpp
namespace examples
{


struct country
{
	std::string name_;
	std::vector<city> cities_;
	std::vector<city>::size_type capital_index_;
};



}


#endif
