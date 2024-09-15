function(target_set_warnings TARGET ENABLED ENABLED_AS_ERRORS)
    if (NOT ${ENABLED})
        message(STATUS "Hello : Warnings Disabled for: ${TARGET}")
        return()
    endif()

    message(STATUS "Hello : Warnings Enabled for: ${TARGET}")

    set(MSVC_WARNINGS
        /W4
        /permissive-)

    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic)

    set(GCC_WARNINGS
        ${CLANG_WARNINGS})

    if(${ENABLED_AS_ERRORS})
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
    endif()

    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${TARGET} PRIVATE ${WARNINGS})
    set(HELLO_MSG "Hello : " ${WARNINGS})
    message(STATUS ${HELLO_MSG})

endfunction(target_set_warnings)
