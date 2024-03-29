// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef GRAMMAR_F628CCE8_06DD_43A9_BEE3_C3EB343AC539
#define GRAMMAR_F628CCE8_06DD_43A9_BEE3_C3EB343AC539


#include <string>


namespace sx
{


namespace genesis
{


extern const std::string condition_modifier_NOT;
extern const std::string condition_modifier_NONE;
extern const char DELIMITER_CHAR;
extern const char LINE_BREAK_CHAR;		
extern const char OPEN_PARENTHESIS_CHAR;		
extern const char CLOSE_PARENTHESIS_CHAR;		
extern const char COMMA_CHAR;		
extern const std::string COMMA_CLOSE_PARENTHESIS;
extern const std::string VARIABLE_COMMAND;		
extern const std::string LOOP_START_COMMAND;		
extern const std::string LOOP_END_COMMAND;		
extern const std::string IF_START_COMMAND;		
extern const std::string IF_END_COMMAND;
extern const std::string SWITCH_START_COMMAND;
extern const std::string SWITCH_END_COMMAND;
extern const std::string SWITCH_CASE_START_COMMAND;
extern const std::string SWITCH_CASE_END_COMMAND;
extern const std::string SWITCH_DEFAULT_START_COMMAND;
extern const std::string SWITCH_DEFAULT_END_COMMAND;
extern const int SWITCH_DEFAULT_INDEX_VALUE;
extern const std::string TEMPLATE_COMMAND;
extern const char NEW_LINE_CHAR;
extern const std::size_t SIZE_ONE;
extern const char INDENT_CHAR;


}


}


#endif
