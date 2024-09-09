#https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html
cmake_minimum_required(VERSION 3.16.0)

project(MathGTest VERSION 1.0.0 LANGUAGES C CXX)

set(EXE_NAME MathProj)
set(LIB_NAME MathLib)

add_executable(${EXE_NAME} mathproj.cpp)
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})

add_subdirectory(mathlib)
