cmake_minimum_required(VERSION 3.0)

if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()


function(use_pthread varName)
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(${varName} ${${varName}} pthread PARENT_SCOPE)
	endif()
endfunction()


function(add_library_for_linking varName libraryName)
	set(${varName} ${${varName}} ${libraryName} PARENT_SCOPE)
endfunction()
