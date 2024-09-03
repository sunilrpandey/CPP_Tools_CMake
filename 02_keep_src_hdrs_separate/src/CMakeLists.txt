add_library(Library STATIC fun_lib.cpp)

add_executable(Executable 02_src_hdrs_in_separate_dir.cpp)
target_link_libraries(Executable PUBLIC Library)