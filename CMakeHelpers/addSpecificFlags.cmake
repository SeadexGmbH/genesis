cmake_minimum_required(VERSION 3.0)

if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

add_compiler_flag("-Wall")

if(NOT DEFINED CPP_VERSION)
	set(CPP_VERSION "17")
elseif("${CPP_VERSION}" STREQUAL "03")	
	message(SEND_ERROR "Error: C++03 is no longer supported!")
endif()


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

	if(DEFINED CPP_VERSION AND "${CPP_VERSION}" STREQUAL "03")
			message(SEND_ERROR "Error: C++03 is no longer supported!")
	endif()


	#gcc/clang compiler flags
	if(NOT "SX_PEDANTIC" STREQUAL "OFF")
		add_compiler_flag("-pedantic")
	endif()
	
	# for release
	if( "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
		message(STATUS "Build release.")
		add_compiler_flag("-s ")
	elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		message(STATUS "Build debug.")
	else()
		message(WARNING "No build type selected via CMAKE_BUILD_TYPE!")
	endif()
	
	add_compiler_flag("-std=c++${CPP_VERSION}")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	# Checks buffer security.
	set(extra_flags "${extra_flags} /GS")
	
	#Sets output warning level.
	set(extra_flags "${extra_flags} /W4")
	
	#Disable specific Warnings.
	set(extra_flags "${extra_flags} /wd\"4127\" /wd\"4250\"")
	
	#Defines constants and macros.
	set(extra_flags "${extra_flags} /D \"_CRT_SECURE_NO_WARNINGS\"")
	
	#Enables function-level linking.
	set(extra_flags "${extra_flags} /Gy")
	
	#Specifies standard behaviour under /Ze.
	set(extra_flags "${extra_flags} /Zc:wchar_t /Zc:inline")
	
	#Disable minimal rebuild.
	set(extra_flags "${extra_flags} /Gm-")
	
	#Enables additional security features and warnings.
	set(extra_flags "${extra_flags} /sdl")
			
	#Specifies floating-point behaviour.
	set(extra_flags "${extra_flags} /fp:precise")
		
	#Multibyte character sets macro.
	set(extra_flags "${extra_flags} /D \"_MBCS\"")
		
	#Enables you to provide internal compiler error (ICE) information directly to the Visual C++ team.
	set(extra_flags "${extra_flags} /errorReport:prompt")
	
	#Treats warnings as errors.
	if( "${MSVC_VERSION}" STRGREATER "1800" )
		set(extra_flags "${extra_flags} /WX")
	#else( "${MSVC_VERSION}" STRLESS "1900" )
	else()
		set(extra_flags "${extra_flags} /WX-")
	endif()
		
	
	#Generates intrinsic functions.
	set(extra_flags "${extra_flags} /Oi")
	
	#Specifies the model of exception handling.
	set(extra_flags "${extra_flags} /EHsc")
	
	#Creates an object file.
	set(extra_flags "${extra_flags} /Fo")
	
	#Marks an executable as verified to be compatible with the Windows Data Execution Prevention feature.
	#set(extra_flags "${extra_flags} /NXCOMPAT")
	

	# for release
	if( "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
		#Creates fast code.
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /PDB-")
		
		#Controls LINK optimizations.
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
		
	# for debug
	elseif( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )	
		#Creates a program database (PDB) file.
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /PDB")
	endif()

	add_compiler_flag("/std=c++${CPP_VERSION}")

endif()

set(CMAKE_CXX_STANDARD ${CPP_VERSION})
message(STATUS "C++ standard set to c++${CPP_VERSION}.")
