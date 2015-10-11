cmake_minimum_required(VERSION 3.3)
project(Tarea1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES_TESTS main.c main.h brute_force.c brute_force.h kmp.c kmp.h
        boyermoore.c boyermoore.h generator.h generator.c)
set(SOURCE_FILES_GENERATOR generator.c generator.h generator_main.c generator_main.h)
add_executable(Tarea1 ${SOURCE_FILES_TESTS} )
add_executable(Generator ${SOURCE_FILES_GENERATOR} )