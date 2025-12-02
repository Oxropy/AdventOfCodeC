cmake_minimum_required(VERSION 4.0)
project(AdventOfCodeC C)

set(CMAKE_C_STANDARD 23)

add_executable(AdventOfCodeC
        src/year2025/Day01.c
        src/file_reader_helper.c)
add_executable(Day01
        src/year2025/Day01.c)
