cmake_minimum_required(VERSION 3.8)

project(html_page_generator)

file(GLOB html_page_generator_SRC "./*.hpp" "./*.cpp" "./../../genesis/include/*.hpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(./../../CMakeHelpers/addSpecificFlags.cmake)
include(./../../CMakeHelpers/addSeadexOptions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")

add_executable(html_page_generator ${html_page_generator_SRC})

set(link_libraries_list "")


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_library_for_linking(link_libraries_list genesis)
	
	if((NOT "${FMT_LIB_INCLUDE}" STREQUAL "") AND (NOT "${FMT_LIB}" STREQUAL "") AND 
	(NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "") AND (NOT "${SPDLOG_LIB}" STREQUAL "") AND 
	(NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "") AND (NOT "${ESSENTIALS_LIB}" STREQUAL ""))
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D \"SPDLOG_FMT_EXTERNAL\"")
		
		add_library_for_linking(link_libraries_list "${FMT_LIB}")
		add_library_for_linking(link_libraries_list "${SPDLOG_LIB}")
		add_library_for_linking(link_libraries_list "${ESSENTIALS_LIB}")
	else()
		target_link_directories(html_page_generator PUBLIC ${CMAKE_LIBRARY_PATH})
		add_library_for_linking(link_libraries_list essentials)
	endif()
else()
	add_library_for_linking(link_libraries_list libgenesis)
	
	if((NOT "${FMT_LIB_INCLUDE}" STREQUAL "") AND (NOT "${FMT_LIB}" STREQUAL "") AND 
	(NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "") AND (NOT "${SPDLOG_LIB}" STREQUAL "") AND 
	(NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "") AND (NOT "${ESSENTIALS_LIB}" STREQUAL ""))
		add_library_for_linking(link_libraries_list "${FMT_LIB}")
		add_library_for_linking(link_libraries_list "${SPDLOG_LIB}")
		add_library_for_linking(link_libraries_list "${ESSENTIALS_LIB}")
		set(THREADS_PREFER_PTHREAD_FLAG ON)
		find_package(Threads REQUIRED)
		target_link_libraries(html_page_generator PRIVATE Threads::Threads)
	else()
		target_link_directories(html_page_generator PUBLIC ${CMAKE_LIBRARY_PATH})
		add_library_for_linking(link_libraries_list libessentials.so)
		find_package(Threads REQUIRED)
		add_library_for_linking(link_libraries_list Threads::Threads)
	endif()
endif()

include_directories("./../../genesis/include")

if((NOT "${FMT_LIB_INCLUDE}" STREQUAL "") AND (NOT "${FMT_LIB}" STREQUAL "") AND 
(NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "") AND (NOT "${SPDLOG_LIB}" STREQUAL "") AND 
(NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "") AND (NOT "${ESSENTIALS_LIB}" STREQUAL ""))
	include_directories("${FMT_LIB_INCLUDE}")
	include_directories("${SPDLOG_LIB_INCLUDE}")
	include_directories("${ESSENTIALS_LIB_INCLUDE}")
else()
	include_directories("${CMAKE_INCLUDE_PATH}")
	target_link_directories(html_page_generator PUBLIC ${CMAKE_LIBRARY_PATH})
endif()

message(STATUS "html_page_generator linking to libraries: ${link_libraries_list}" )

TARGET_LINK_LIBRARIES(html_page_generator LINK_PUBLIC ${link_libraries_list})

install(TARGETS html_page_generator DESTINATION bin)
