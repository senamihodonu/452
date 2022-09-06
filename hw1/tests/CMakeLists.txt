cmake_minimum_required(VERSION 3.22.1)

set(This deq_tests)

set(Sources
    deq_tests.cpp
)

project(${This} C CXX)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    deq
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
