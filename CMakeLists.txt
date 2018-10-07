cmake_minimum_required(VERSION 2.8)
project(paa_project)

set(SOURCE_FILES src/algorithms.cpp src/Graph.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include_directories(include)

add_executable(paa_project main.cpp ${SOURCE_FILES})