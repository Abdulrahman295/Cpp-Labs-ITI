cmake_minimum_required(VERSION 4.0)
project(Lab12)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab12 main.cpp
        lib/GeoShape.cpp
        lib/GeoShape.h
        lib/Rect.cpp
        lib/Rect.h
        lib/Triangle.cpp
        lib/Triangle.h
        lib/Circle.cpp
        lib/Circle.h
        lib/Square.cpp
        lib/Square.h)
