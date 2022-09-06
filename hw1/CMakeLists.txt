cmake_minimum_required(VERSION 3.22.1)

set(This deq)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    deq.h
    error.h
)

set(Sources
    deq.c
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)