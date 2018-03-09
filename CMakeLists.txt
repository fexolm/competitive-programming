cmake_minimum_required(VERSION 2.8)

project(competitive-programming)
set(CMAKE_CXX_STANDART 17)

add_subdirectory(Tests)

file(GLOB SOURCES "algorithms/*" "data-structures/*")

include_directories(${CMAKE_SOURCE_DIR})

add_library(cp SHARED ${SOURCES} def.hpp)

set_target_properties(cp PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()
