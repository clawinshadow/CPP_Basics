cmake_minimum_required(VERSION 3.0.0)
project(CPP_Basics VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(CPP_Basics main.cpp 
    Chapter2/cpp_initiation.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
