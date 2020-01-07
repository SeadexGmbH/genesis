cmake_minimum_required(VERSION 3.8)

project(genesis)

set(CMAKE_VERBOSE_MAKEFILE, 1)

file(GLOB genesis_SRC "include/*.hpp" "source/*.cpp")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(./../CMakeHelpers/addSpecificFlags.cmake)
include(./../CMakeHelpers/addSeadexOptions.cmake)

include_directories("./include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_library(genesis STATIC ${genesis_SRC})

	if( NOT "${FMT_LIB_INCLUDE}" STREQUAL "" AND NOT "${FMT_LIB}" STREQUAL "" AND NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "" AND NOT "${SPDLOG_LIB}" STREQUAL ""
	AND NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "" AND NOT "${ESSENTIALS_LIB}" STREQUAL "")
		#target_link_libraries(genesis LINK_PUBLIC "${ESSENTIALS_LIB}")
		include_directories("${FMT_LIB_INCLUDE}")
		include_directories("${SPDLOG_LIB_INCLUDE}")
		include_directories("${ESSENTIALS_LIB_INCLUDE}")
		TARGET_LINK_LIBRARIES(genesis "${FMT_LIB}")
		TARGET_LINK_LIBRARIES(genesis "${SPDLOG_LIB}")
		TARGET_LINK_LIBRARIES(genesis "${ESSENTIALS_LIB}")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D \"SPDLOG_FMT_EXTERNAL\"")
		message(STATUS "[lib genesis] libessentials, libfmt or spdlog paths provided by user.")
	else()
		include_directories("${CMAKE_INCLUDE_PATH}")
		message(STATUS "[lib genesis] No essentials, libfmt or spdlog paths provided by user. Include Conan libraries headers.")
	endif()

else()
	# GNU, Clang, Apple-Clang
	add_library(libgenesis ${LINK_TYPE} ${genesis_SRC})

	if( NOT "${FMT_LIB_INCLUDE}" STREQUAL "" AND NOT "${FMT_LIB}" STREQUAL "" AND NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "" AND NOT "${SPDLOG_LIB}" STREQUAL ""
	AND NOT "${ESSENTIALS_LIB_INCLUDE}" STREQUAL "" AND NOT "${ESSENTIALS_LIB}" STREQUAL "")
		include_directories("${FMT_LIB_INCLUDE}")
		include_directories("${SPDLOG_LIB_INCLUDE}")
		include_directories("${ESSENTIALS_LIB_INCLUDE}")
		TARGET_LINK_LIBRARIES(libgenesis ${FMT_LIB})
		TARGET_LINK_LIBRARIES(libgenesis ${SPDLOG_LIB})
		TARGET_LINK_LIBRARIES(libgenesis ${ESSENTIALS_LIB})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D \"SPDLOG_FMT_EXTERNAL\"")
	else()
		TARGET_LINK_LIBRARIES(libgenesis ${CONAN_LIBS})	
		include_directories("${CMAKE_INCLUDE_PATH}")
		message(STATUS "[lib genesis] No essentials, libfmt or spdlog paths provided by user. Include Conan libraries headers.")
	endif()

endif()

if( NOT "${FMT_LIB_INCLUDE}" STREQUAL "" AND NOT "${FMT_LIB}" STREQUAL "" AND NOT "${SPDLOG_LIB_INCLUDE}" STREQUAL "" AND NOT "${SPDLOG_LIB}" STREQUAL "")
	include_directories("${ESSENTIALS_LIB_INCLUDE}")
	include_directories("${SPDLOG_LIB_INCLUDE}")
	include_directories("${FMT_LIB_INCLUDE}")
else()
	include_directories(${CONAN_INCLUDE_DIRS})	
endif()

file(GLOB genesis_hpp "./include/*.hpp")
install(FILES ${genesis_hpp} DESTINATION include/genesis/)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	install(TARGETS genesis DESTINATION lib)
	set_target_properties(genesis PROPERTIES PREFIX "")
else()
	# GNU, Clang, Apple-Clang
	install(TARGETS libgenesis DESTINATION lib)
	set_target_properties(libgenesis PROPERTIES PREFIX "")
endif()
