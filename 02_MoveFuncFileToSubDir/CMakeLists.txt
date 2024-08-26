
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

add_subdirectory(fun_lib)

add_executable(Executable 02_move_funcs_to_sub_dir.cpp)
target_link_libraries(Executable PUBLIC Library)
