
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)


#add_executable(Executable 01_move_funcs_to_separate_files.cpp fun_lib.cpp)

# When we use library to call certain function
add_executable(Executable 01_move_funcs_to_separate_files.cpp)

add_library(Library STATIC fun_lib.cpp)
target_link_libraries(Executable PUBLIC Library)
