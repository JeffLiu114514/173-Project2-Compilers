cmake_minimum_required(VERSION 3.23)
project(173Proj2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(173Proj2 main.c Recursive.c Recursive.h stack.c stack.h table.c table.h)
