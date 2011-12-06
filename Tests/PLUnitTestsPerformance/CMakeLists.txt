#*********************************************************#
#*  File: CMakeLists.txt                                 *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


##################################################
## Project
##################################################
define_project(PLUnitTestsPerformance NOSUFFIX)

##################################################
## Source files
##################################################
add_sources(
	src/UnitTestsPerformance.cpp
	# PLCore
	src/PLCore/Container/Hashmap.cpp
	# UnitTest++ AddIns
	../PLUnitTests/src/UnitTest++AddIns/MyTestReporter.cpp
	../PLUnitTests/src/UnitTest++AddIns/MyMobileTestReporter.cpp
	../PLUnitTests/src/UnitTest++AddIns/RunAllTests.cpp
	../PLUnitTests/src/UnitTest++AddIns/wchar_template.cpp
)
if(ANDROID)
	add_sources(
		src/MainAndroid.cpp
	)
else()
	add_sources(
		src/Main.cpp
	)
endif()

##################################################
## Include directories
##################################################
add_include_directories(
	include
	${UNITTESTPP_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/Base/PLCore/include
	../PLUnitTests/include/
)

##################################################
## Library directories
##################################################
add_link_directories(
	${PL_LIB_DIR}
)

##################################################
## Additional libraries
##################################################
add_libs(
	${UNITTESTPP_LIBRARIES}
	PLCore
)

##################################################
## Preprocessor definitions
##################################################
if(WIN32)
	##################################################
	## Win32
	##################################################
	add_compile_defs(
		${WIN32_COMPILE_DEFS}
		_ITERATOR_DEBUG_LEVEL=0
	)
elseif(LINUX)
	##################################################
	## Linux
	##################################################
	add_compile_defs(
		${LINUX_COMPILE_DEFS}
	)
endif()

##################################################
## Compiler flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_compile_flags(
		${WIN32_COMPILE_FLAGS}
		/EHsc			# Enable exception handling for this project
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	add_compile_flags(
		${LINUX_COMPILE_FLAGS}
		-fexceptions	# Enable exception handling for this project
	)
endif()

##################################################
## Linker flags
##################################################
if(WIN32)
	##################################################
	## MSVC Compiler
	##################################################
	add_linker_flags(
		${WIN32_LINKER_FLAGS}
	)
elseif(LINUX)
	##################################################
	## GCC Compiler
	##################################################
	if(ANDROID)
		add_linker_flags(
			-L${STL_LIBRARIES_PATH}	# UnitTest++ is using stl, adding this line results in slightly bigger executables so we don't do this within "LinuxNDK.cmake"
		)
	endif()
	add_linker_flags(
		${LINUX_LINKER_FLAGS}
	)
endif()

##################################################
## Build
##################################################
if(ANDROID)
	build_library(${CMAKETOOLS_CURRENT_TARGET} SHARED)
else()
	build_executable(${CMAKETOOLS_CURRENT_TARGET} CONSOLE)
endif()

##################################################
## Dependencies
##################################################
add_dependencies(${CMAKETOOLS_CURRENT_TARGET}	PLCore External-UnitTest++)
add_dependencies(Tests							${CMAKETOOLS_CURRENT_TARGET})

##################################################
## Post-Build
##################################################

if(ANDROID)
	# Dynamic library
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_SHARED_LIB} ${PL_TESTS_BIN_DIR}
	)
else()
	# Executable
	add_custom_command(TARGET ${CMAKETOOLS_CURRENT_TARGET}
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKETOOLS_CURRENT_OUTPUT_DIR}/${CMAKETOOLS_CURRENT_EXECUTABLE} ${PL_TESTS_BIN_DIR}
	)
endif()
