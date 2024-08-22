project(pot)
cmake_minimum_required(VERSION 3.22)

FILE(GLOB mysrc ./src/*.cpp)

add_executable(pot ${mysrc})
