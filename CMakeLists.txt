cmake_minimum_required(VERSION 3.25)
project(Shudo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Shudo main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")