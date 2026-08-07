cmake_minimum_required(VERSION 3.20)

project(Cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
        Cpp
        main.cpp
        src/Motor.cpp
)
