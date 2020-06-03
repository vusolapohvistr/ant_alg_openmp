cmake_minimum_required(VERSION 3.16)
project(ant_alg_openmp)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("/openmp:experimental")

add_executable(ant_alg_openmp main.cpp Ant.cpp Ant.h AntAlg.cpp AntAlg.h)