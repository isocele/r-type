cmake_minimum_required(VERSION 3.10)
project(cpp_rtype_2018)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
		message(STATUS "No build type selected, default to Debug")
		set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
	endif()
endif()

set(CMAKE_CXX_STANDARD 14)
add_definitions("-g3")

## set compiler flags depending on OS and compiler
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# add cmake.conan file if missing
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")

	if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/conan.cmake")
		message(FATAL_ERROR "Missing conan.cmake setup file")
	endif()

	message("-- Copying conan.cmake setup file...")
	configure_file("${CMAKE_CURRENT_LIST_DIR}/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake" COPYONLY)

endif()

include_directories(.)
include_directories(./include)
include_directories(${CMAKE_BINARY_DIR})
include (${CMAKE_BINARY_DIR}/conan.cmake)

## Check conan installation
conan_check()

## Add remote conan libs
conan_add_remote(NAME public INDEX 1
	URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_add_remote(NAME center INDEX 2
	URL https://bintray.com/conan/conan-center)
conan_add_remote(NAME tek INDEX 3
	URL https://bintray.com/bincrafters/public-conan)

#Install package with the command 'conan install ./conanfile.txt'
conan_cmake_run(CONANFILE conanfile.txt
	BASIC_SETUP
	BUILD missing)

add_executable(r-type_server
	include/Server.hpp
	include/Component.hpp
	include/Entity.hpp
	include/Mediator.hpp
	include/System.hpp
	include/GameEngine.hpp
	include/Utils.hpp
	include/CombatComponent.hpp
	include/GraphicalComponent.hpp
	include/PositionComponent.hpp
	include/MoveSystem.hpp
	include/FightSystem.hpp
	src/Main.cpp
	src/Server.cpp
	src/ServerUtils.cpp
	src/Component.cpp
	src/Entity.cpp
	src/Utils.cpp
	src/Mediator.cpp
	src/System.cpp
	src/GameEngine.cpp
	src/CombatComponent.cpp
	src/GraphicalComponent.cpp
	src/PositionComponent.cpp
	src/MoveSystem.cpp
	src/FightSystem.cpp
	src/ImplementEngineUpdate.cpp
	)

## target build libs
target_link_libraries(r-type_server ${CONAN_LIBS})
