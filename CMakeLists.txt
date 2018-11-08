cmake_minimum_required(VERSION 3.12)
project(DominatingSet)

set(CMAKE_CXX_STANDARD 14)

add_executable(DominatingSet main.cpp src/Graph.cpp src/Algorithms.cpp include/Graph.h include/Algorithms.h include/Edge.h include/Types.h)