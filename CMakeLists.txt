cmake_minimum_required(VERSION 3.0.0)

project(CPP_Basics)

add_executable(CPP_Basics main.cpp 
    Chapter2/cpp_initiation.cpp
    Chapter2/cpp_initiation_2.cpp
    Chapter2/data_types.cpp
    Chapter2/scopes_linkage/file1.cpp
    Chapter2/scopes_linkage/file2.cpp
    Chapter3/string_vector_array.cpp
    Chapter4/expressions.cpp
    Chapter5/statements.cpp
    Chapter6/functions.cpp
    Chapter7/class_basic.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message("${CMAKE_CXX_FLAGS}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CMAKE_CXX_STANDARD 11)

