cmake_minimum_required(VERSION 2.8)
project(amazontruck)

# static library headers
include_directories(include)

include_directories(src)


add_executable(amazontruck
    src/Driver.cpp
    src/AmazonTruck.cpp
)

target_compile_features(amazontruck PRIVATE cxx_std_11)
# warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsyntax-only")
