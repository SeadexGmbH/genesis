// Copyright (c) 2017-, Seadex GmbH
// The Seadex GmbH licenses this file to you under the MIT license.
// The license file can be found in the license directory of this project.
// This file is part of the Seadex genesis library (http://genesis.seadex.de).

#ifndef RECIPE_CALLBACK_IMPL_D1209279_561E_435D_B6DC_68F2A50937C2
#define RECIPE_CALLBACK_IMPL_D1209279_561E_435D_B6DC_68F2A50937C2


#include "recipe_callback.hpp"

#include "config.hpp"


namespace examples
{


class recipe_callback_impl final
	: public sx::genesis::recipe_callback
{
public:
	explicit recipe_callback_impl( const config& _config );
	virtual ~recipe_callback_impl() noexcept override;
	SXE_NO_COPY( recipe_callback_impl )
	virtual std::string get_variable_content( const std::string& _variable_name ) override;
	virtual void before_loop( const std::string& _loop_name ) override;
	virtual void before_loop_iteration( [[ maybe_unused ]] const std::string& _loop_name ) override;
	virtual void after_loop_iteration( const std::string& _loop_name ) override;
	virtual bool check_loop_condition( const std::string& _loop_name ) const override;
	virtual void after_loop( [[ maybe_unused ]] const std::string& _loop_name ) override;
	virtual bool check_condition( const std::string& _condition_name ) const override;
	virtual void condition_begin( [[ maybe_unused ]] const std::string& _condition_name ) override;
	virtual void condition_end( [[ maybe_unused ]] const std::string& _condition_name ) override;
	virtual int get_switch_case( const std::string& _switch_name ) override;


private:
	const config& config_;
	std::size_t country_index_;
	std::size_t city_index_;
};


}


#endif
