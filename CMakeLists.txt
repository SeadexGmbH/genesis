cmake_minimum_required(VERSION 3.8)

project(genesis_all)

include(./CMakeHelpers/functions.cmake)
include(./CMakeHelpers/functionsAddCompilerFlags.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D \"FMT_HEADER_ONLY\"  -D \"SPDLOG_FMT_EXTERNAL\"")

if( (NOT "${FMT_LIB_INCLUDE}" STREQUAL "") AND (NOT "${FMT_LIB}" STREQUAL "") AND (NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "") AND (NOT "${SPDLOG_LIB}" STREQUAL "") AND (NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "") AND (NOT "${ESSENTIALS_LIB}" STREQUAL "") )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D \"SPDLOG_FMT_EXTERNAL\"")
	message(STATUS "essentials library, libfmt or spdlog paths provided by user.")
else()
	if(EXISTS "${PROJECT_SOURCE_DIR}/build/conan_toolchain.cmake")
		message(STATUS "Using Conan.")
		set(SPDLOG_FMT_EXTERNAL ON CACHE  BOOL "")	
	else()
		message(STATUS "Conan CMake file not present. Conan is not used.")
	endif()
endif()

add_subdirectory(genesis)

if(GEN_BUILD_EXAMPLES AND EXISTS "${PROJECT_SOURCE_DIR}/examples")
	message(STATUS "Build examples.")
	add_subdirectory(examples)
endif()