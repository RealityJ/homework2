cmake_minimum_required(VERSION 3.3)
project(homework2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(homework2 ${SOURCE_FILES})