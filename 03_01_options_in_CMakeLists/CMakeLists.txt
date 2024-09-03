
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)


# some pre-defined variables
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

#define  your own variables
set(EXE_NAME "Make_Exe")
set(LIB_NAME Func_Lib) # quote or no quote both works


add_subdirectory(libs)

#set options for condition cmake
option(COMPILE_EXECUTABLE "Whether to compile the executable" OFF)
if (COMPILE_EXECUTABLE)
    add_subdirectory(app)
    message("Exe is to be compiled!!")
else()
    message("Without exe compiling!!")
endif()
