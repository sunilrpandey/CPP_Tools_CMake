cmake_minimum_required(VERSION 3.16)

project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(EXE_NAME "Make_Exe")
set(LIB_NAME Func_Lib)

add_subdirectory(configured)
add_subdirectory(libs)
add_subdirectory(app)
