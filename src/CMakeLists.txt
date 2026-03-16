cmake_minimum_required(VERSION 3.10)

project(Project1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(project1
        main.cpp
        parser.cpp
)