cmake_minimum_required(VERSION 2.8)

project(competitive-programming-tests)

set(CMAKE_CXX_STANDART 14)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

enable_testing()

add_executable(segment_tree_test segment_tree_test.cpp)
add_executable(cartesian_tree_test CartesianTree_test.cpp)

target_link_libraries(segment_tree_test cp ${Boost_LIBRARIES})
target_link_libraries(cartesian_tree_test cp ${Boost_LIBRARIES})


add_test(segment-tree-test segment_tree_test)
add_test(cartesian_tree_test cartesian_tree_test)


