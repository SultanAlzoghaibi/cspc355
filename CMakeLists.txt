cmake_minimum_required(VERSION 3.31)
project(cspc355notes C)

set(CMAKE_C_STANDARD 11)

# Assignment 1 target
add_executable(A1
        A1/main1.c
        copy.c
        midtermprerp/test.c
)

# Assignment 2 target
add_executable(A2
        A2/main.c
        copy.c
)

# (Optional) Assembly example
add_executable(assembly
        assembly/main.S
)