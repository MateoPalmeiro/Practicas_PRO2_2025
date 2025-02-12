#PLEASE, DO NOT CHANGE THIS FILE
cmake_minimum_required(VERSION 3.5)
project(P1 C)
set(CMAKE_C_STANDARD 99)

# Si no estan definidas las variables impl e input, se les asignan valores por defecto.
if(NOT DEFINED impl)
    # choose between DYNAMIC or STATIC to use a concrete implementation (uncomment desired line)
    # set(impl DYNAMIC)
    set(impl STATIC)
endif()

if(NOT DEFINED input)
    # choose the input file for main (new.txt, delete.txt, bid.txt ...)
    set(input new.txt)
endif()

include(config.cmake)

if(impl STREQUAL STATIC)
    add_definitions(-DSTATIC_LIST)
    set(dependencies static_list.h static_list.c)
elseif(impl STREQUAL DYNAMIC)
    add_definitions(-DDYNAMIC_LIST)
    set(dependencies dynamic_list.h dynamic_list.c)
endif()

set(CMAKE_VERBOSE_MAKEFILE true)
add_definitions(-DINPUT_FILE="${input}")
add_executable(main main.c types.h ${dependencies})
add_executable(test_lists types.h test.c ${dependencies})
target_compile_options(main PRIVATE -Wall -Wextra)
target_compile_options(test_lists PRIVATE -Wall -Wextra)

# Cambiar el directorio de salida para que se ubique en el bin del directorio raiz del repo
set_target_properties(main test_lists PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
