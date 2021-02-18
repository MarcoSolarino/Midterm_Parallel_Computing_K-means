cmake_minimum_required(VERSION 3.17)
project(Kmeans)

# set(CMAKE_CXX_FLAGS "-std=c++14 -lstdc++fs")
set(CMAKE_CXX_STANDARD 14)


add_executable(Kmeans KmeansSequential.cpp Point.cpp Point.h csvHandler.h csvHandler.cpp operations.cpp operations.h)
# target_link_libraries(Kmeans stdc++fs)
