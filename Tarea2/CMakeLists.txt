cmake_minimum_required(VERSION 3.3)
project(Tarea2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(SOURCE_FILES main.c main.h btree.c btree.h hash.c hash.h ext_hashing.c ext_hashing.h)
add_executable(Tarea2 ${SOURCE_FILES})