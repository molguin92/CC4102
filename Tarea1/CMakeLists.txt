cmake_minimum_required(VERSION 3.3)
project(Tarea1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c main.h brute_force.c brute_force.h generator.c generator.h )
add_executable(Tarea1 ${SOURCE_FILES} )