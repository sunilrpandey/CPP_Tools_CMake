#https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html
cmake_minimum_required(VERSION 3.16.0)

project(MathGTest VERSION 1.0.0 LANGUAGES C CXX)

set(EXE_NAME MathProj)
set(LIB_NAME MathLib)

include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG         v1.15.2
#   GIT_SHALLOW TRUE # Wont download code recursively
# )


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(${EXE_NAME} mathproj.cpp)
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})

add_subdirectory(mathlib)

enable_testing()

add_executable(
  test_mathproj
  test_mathproj.cpp
)
target_link_libraries(
    test_mathproj
    GTest::gtest_main
    ${LIB_NAME}
)

include(GoogleTest)
gtest_discover_tests(test_mathproj)
