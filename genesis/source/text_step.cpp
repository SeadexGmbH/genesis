// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#include "text_step.hpp"

#include <iostream>

#include "recipe_callback.hpp"
#include "grammar.hpp"


namespace sx
{


namespace genesis
{


text_step::text_step( const std::string& _text ) :
	recipe_step(),
	text_( _text )
{
	// Nothing to do...
}


text_step::~text_step() noexcept
{
	// Nothing to do...
}


void text_step::create( [[maybe_unused]] recipe_callback& _recipe_callback, std::stringstream& _ostream, const int _indent )
{
	const std::string indent = create_indent( _indent);
	const std::vector<std::string> lines = split();
	for( std::vector<std::string>::size_type i = 0; i < lines.size(); ++i )
	{
		_ostream << lines[ i ];
		if(i != lines.size() - 1)
		{
			_ostream << NEW_LINE_CHAR << indent;
		}
	}
}


std::vector<std::string> text_step::split() const
{
	std::vector<std::string> lines;

	std::string::size_type position = 0;
	std::string::size_type previous = 0;
	while( ( position = text_.find( NEW_LINE_CHAR, previous ) ) != std::string::npos )
	{
		lines.push_back( text_.substr( previous, position - previous ) );
		previous = position + 1;
	}

	lines.push_back( text_.substr( previous ) );

	return( lines );
}


std::string text_step::create_indent( const int _indent )
{
	std::stringstream indent;
	for(int i = 0; i < _indent; ++i) {
		indent << INDENT_CHAR;
	}
	return(indent.str());
}


}


}
