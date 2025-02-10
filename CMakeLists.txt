cmake_minimum_required(VERSION 3.28)
project(P0_2025 C)

set(CMAKE_C_STANDARD 99)

# ==================================================================
# Para seleccionar el modo, comenta o descomenta la siguiente línea:
#
# Si descomentas la siguiente línea, se compilará en modo "struct"
# (es decir, se usará rational_struct.c y se definirá la macro STRUCT_MODE)
#
# Si la línea permanece comentada, se compilará en modo "punteros"
# (se usará rational_pointer.c)
# ==================================================================
# set(USE_STRUCT_MODE ON)

if(DEFINED USE_STRUCT_MODE)
    add_definitions(-DSTRUCT_MODE)
    message(STATUS "Compilando en Modo Struct (STRUCT_MODE definido).")
    set(SOURCES main.c rational_struct.c)
else()
    message(STATUS "Compilando en Modo Punteros (STRUCT_MODE NO definido).")
    set(SOURCES main.c rational_pointer.c)
endif()

add_executable(P0_2025 ${SOURCES})
