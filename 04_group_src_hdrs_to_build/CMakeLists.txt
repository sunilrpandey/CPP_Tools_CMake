cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

set(LIB_NAME
        "func_lib")

set(EXE_NAME
        "04_group_src_hdrs_to_build")

add_subdirectory(libs)
add_executable(${EXE_NAME} 04_group_src_hdrs_to_build.cpp)
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})
