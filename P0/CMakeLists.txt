cmake_minimum_required(VERSION 3.28)
project(P0_2025 C)

set(CMAKE_C_STANDARD 99)

# ==================================================================
# para seleccionar el modo, comenta o descomenta la siguiente línea:
#
# si descomentas la siguiente linea, se compilara en modo "struct"
# (es decir, se usara rational_struct.c y se definira la macro STRUCT_MODE)
#
# Si la linea permanece comentada, se compilara en modo "punteros"
# (se usara rational_pointer.c)
# ==================================================================
set(USE_STRUCT_MODE ON)

if(DEFINED USE_STRUCT_MODE)
    add_definitions(-DSTRUCT_MODE)
    message(STATUS "Compilando en Modo Struct (STRUCT_MODE definido).")
    set(SOURCES main.c rational_struct.c)
else()
    message(STATUS "Compilando en Modo Punteros (STRUCT_MODE NO definido).")
    set(SOURCES main.c rational_pointer.c)
endif()

add_executable(P0_2025 ${SOURCES})
