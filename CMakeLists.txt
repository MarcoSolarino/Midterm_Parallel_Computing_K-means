cmake_minimum_required(VERSION 3.17)
project(Kmeans)

set(CMAKE_CXX_STANDARD 14)

add_executable(Kmeans KmeansSequential.cpp Point.cpp Point.h csvhandler.h csvhandler.cpp)