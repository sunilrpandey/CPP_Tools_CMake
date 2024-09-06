
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

set(LIB_NAME
        "func_lib")

set(EXE_NAME
        "mathproj")

add_subdirectory(mathlib)
add_executable(${EXE_NAME} mathproj.cpp)
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
#include(AddGitSubmodule)

#add_git_submodule(external/json)

#add_subdirectory(external)
