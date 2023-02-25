cmake_minimum_required(VERSION 3.24)
project(strsignal C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(strsignal main.c)
