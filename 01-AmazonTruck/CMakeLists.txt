cmake_minimum_required(VERSION 2.8)
project(amazontruck)

# static library headers
include_directories(include)

include_directories(src)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(amazontruck
    src/Driver.cpp
    src/AmazonTruck.cpp
)

# warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsyntax-only")
