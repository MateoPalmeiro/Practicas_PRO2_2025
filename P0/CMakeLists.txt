cmake_minimum_required(VERSION 3.28)
project(P0_2025 C)

set(CMAKE_C_STANDARD 99)

# compila todos los archivos; la seleccion del modo se hace en main.c
add_executable(P0_2025 main.c rational_struct.c rational_pointer.c)
