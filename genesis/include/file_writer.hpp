// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef FILE_WRITER_27D8B8DE_AD70_4536_857C_1D75B5D34EB8
#define FILE_WRITER_27D8B8DE_AD70_4536_857C_1D75B5D34EB8


#include <string>


namespace sx
{


namespace genesis
{


//!\fn void write( const std::string& _file_path, const std::ostream& _output_stream )
//!\brief Function that writes the content of an ostream to the file with the given name.
//!\param _file_path Name of the file that will be written.
//!\param _output_stream Stream that is written to the file.
void write( const std::string& _file_path, const std::ostream& _output_stream );


}


}

#endif
