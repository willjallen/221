cmake_minimum_required(VERSION 2.8)
project(amazontruck)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# static library headers
include_directories(include)

include_directories(src)


add_executable(amazontruck
    src/Driver.cpp
    src/AmazonTruck.cpp
)

# warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsyntax-only")
