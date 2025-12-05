cmake_minimum_required(VERSION 4.0)
project(Lab9)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab9 main.cpp
        lib/MyString.cpp
        lib/MyString.h)
