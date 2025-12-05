cmake_minimum_required(VERSION 4.0)
project(Lab11)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Lab11 main.cpp
        lib/Point.cpp
        lib/Point.h
        lib/Shape.h
        lib/Line.cpp
        lib/Line.h
        lib/Rect.cpp
        lib/Rect.h
        lib/Circle.cpp
        lib/Circle.h
        lib/Picture.cpp
        lib/Picture.h
)

target_link_libraries(Lab11 sfml-graphics sfml-window sfml-system)
