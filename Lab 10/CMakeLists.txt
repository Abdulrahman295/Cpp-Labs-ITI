cmake_minimum_required(VERSION 4.0)
project(Lab10)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab10 main.cpp
        lib/Any.cpp
        lib/Any.h
        lib/PyList.h
        lib/PyList.cpp)
