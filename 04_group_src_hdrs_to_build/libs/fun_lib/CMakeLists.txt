# alternate to below is glob for complete folder but is not preferred
set(LIB_SRCS
        fun_lib1.cpp
        fun_lib2.cpp)

set(LIB_HDRS
        fun_lib1.h
        fun_lib2.h)


add_library(${LIB_NAME} STATIC ${LIB_SRCS} ${LIB_HDRS})
target_include_directories(${LIB_NAME} PUBLIC "./")
