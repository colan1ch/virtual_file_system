cmake_minimum_required(VERSION 3.26)
project(virtual_file_system)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(virtual_file_system
        header.h
        main.cpp
        source.cpp)
