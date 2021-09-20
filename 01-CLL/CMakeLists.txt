cmake_minimum_required(VERSION 2.8)
project(cll)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

add_executable(cll
    src/buffer.cpp
    src/bufferlist.cpp
    src/driver.cpp
)
# all, run, valgrind, clean, and targets to compile each object class individually 
# (Buffer and Bufferlist). 
# add_custom_target(
#     run 
#     ALL 
#     COMMAND ${CMAKE_BINARY_DIR}
#     )

find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $<TARGET_FILE:bftest>)
endif()

# add_custom_target(
#     clean 
#     ALL 
#     COMMAND ${
#     rm -rf *.o
#     rm -f *.out
#     rm -f *~ *.h.gch *#}
#     }

#     )

add_custom_target(Buffer ALL 
    src/buffer.cpp)
add_custom_target(Bufferlist ALL 
    src/bufferlist.cpp)
