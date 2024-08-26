add_library(${LIB_NAME} STATIC fun_lib.cpp)
target_include_directories(${LIB_NAME} PUBLIC
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")
