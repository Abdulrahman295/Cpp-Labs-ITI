cmake_minimum_required(VERSION 4.0)
project(myTUI)

set(CMAKE_CXX_STANDARD 20)

add_executable(myTUI main.cpp
        lib/terminal.h
        lib/terminal.cpp
        lib/delay.h
        lib/delay.cpp)

