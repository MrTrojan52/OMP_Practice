cmake_minimum_required(VERSION 3.15)
project(OMP_Dot_Product)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(OMP_Dot_Product main.cpp)