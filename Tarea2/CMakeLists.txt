cmake_minimum_required(VERSION 3.3)
project(Tarea2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c main.h)
add_executable(Tarea2 ${SOURCE_FILES})