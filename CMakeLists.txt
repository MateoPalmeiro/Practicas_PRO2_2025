cmake_minimum_required(VERSION 3.28)
project(P0_2025 C)

set(CMAKE_C_STANDARD 99)

add_executable(P0_2025 main.c
        cmake-build-debug/rational_struct.c
        cmake-build-debug/rational_struct.h
        cmake-build-debug/rational_pointer.c
        cmake-build-debug/rational_pointer.h)
