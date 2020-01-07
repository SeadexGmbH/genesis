// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef FILE_READER_20EC6A5D_A4B2_4EDC_9B67_57B4B0A0DA31
#define FILE_READER_20EC6A5D_A4B2_4EDC_9B67_57B4B0A0DA31


#include<string>


namespace sx
{


namespace genesis
{


//!\fn bool read( const std::string& _file_path, std::string& _content )
//!\brief Function that reads a file into a given string variable.
//!\param _file_path File that is read.
//!\param _content Target for the content of the file.
//!\return True if the read was successful, false otherwise.
bool read( const std::string& _file_path, std::string& _content );


}


}


#endif
