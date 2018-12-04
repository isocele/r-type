project(r-type)
cmake_minimum_required(VERSION 3.10)
add_definitions("-fPIC")

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

file(GLOB_RECURSE CLT_SRC "Src/*.cpp")
file(GLOB_RECURSE CLT_HDRS "Include/*.hpp")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (CLT_INCLUDE_DIRS "")
foreach (_headerFile ${CLT_HDRS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND CLT_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES CLT_INCLUDE_DIRS)

add_executable(r-type_client ${CLT_SRC})
target_include_directories(r-type_client PRIVATE ${CLT_INCLUDE_DIRS})
target_link_libraries(r-type_client ${CONAN_LIBS})
