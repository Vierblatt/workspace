cmake_minimum_required(VERSION 4.0)
project(work9m8 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(work9m8
        src/main.c
        src/sort.c
        sort.h)
