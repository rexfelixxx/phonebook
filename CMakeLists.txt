cmake_minimum_required(VERSION 3.16)

project(learn_c LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)

add_executable(phonebook main.c)
