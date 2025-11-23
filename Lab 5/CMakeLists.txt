cmake_minimum_required(VERSION 4.0)
project(myTUI)

set(CMAKE_CXX_STANDARD 20)

add_executable(myTUI main.cpp
        lib/key.h
        lib/key.cpp
        lib/terminal.h
        lib/terminal.cpp
        lib/menu.h
        lib/menu.cpp
        lib/employee.h
        lib/employee.cpp
        lib/input.h
        lib/input.cpp)

