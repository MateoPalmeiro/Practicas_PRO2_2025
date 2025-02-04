cmake_minimum_required(VERSION 3.28)
project(P0_2025 C)

set(CMAKE_C_STANDARD 99)

add_executable(P0_2025 main.c
        rational_struct.c
        rational_struct.h
        rational_pointer.c
        rational_pointer.h)
