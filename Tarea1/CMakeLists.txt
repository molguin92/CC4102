cmake_minimum_required(VERSION 3.3)
project(Tarea1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c main.h brute_force.c brute_force.h kmp.c kmp.h
        boyermoore.c boyermoore.h generator.c generator.h)
add_executable(Tarea1 ${SOURCE_FILES} )
target_link_libraries(Tarea1 m)