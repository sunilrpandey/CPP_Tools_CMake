cmake_minimum_required(VERSION 3.23)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

set(LIB_NAME
        "func_lib")

set(EXE_NAME
        "07_add_compile_options")

option(ENABLE_WARNINGS "Enable a Unit Testing" OFF)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
#include(Docs)
include(Warnings)

option(ENABLE_SANITIZE_ADDR "Enable address sanitizer" ON)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitizer" ON)

# and call cmake function
if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
message("------Sanitizer is set---")
    include(Sanitizer)
    add_sanitizer_flags(ENABLE_SANITIZE_ADDR ENABLE_SANITIZE_UNDEF)
endif()

add_executable(${EXE_NAME} 07_add_compile_options.cpp)
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})

add_subdirectory(libs)

if (ENABLE_WARNINGS)
    message("--- Warning enabled-----")
    target_set_warnings(
        ${EXE_NAME}
        ON
        ON
    )
endif()


