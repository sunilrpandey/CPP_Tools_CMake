
# CMake Step by Step

## Hello CMake

Let us assume we have just one implementation (.cpp).  The two basic things that is required for any project is 
- CMake Version
- Project detail
```bash
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)
```
Once header is set add you need to specify if  you want executable or library out of your project
```bash
add_executable(Executable hello_cmake.cpp)
#or
add_library(Library STATIC func_lib.cpp)
```
So here is complete CMakeLists.txt which builds .cpp file with main to executable
```bash
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

add_executable(Executable hello_cmake.cpp)
```
### Build and generate executable/library : all or one
Create Build directory, change directory to build and run cmake
```bash
    mkdir build
	cd build 

    cmake -S .. -B .    # Option 1
    cmake ..            # Option 2
    
    #Specify Generator if required
    cmake -S .. -B . -G "Unix Makefiles" # Option 1
    cmake -S .. -B . -G "Visual Studio 16 2019" # Option 1

    cmake .. -G "Unix Makefiles" # Option 2
    cmake .. -G "Visual Studio 16 2019" # Option 2
    
    
    cmake --build . # this will generate all the libraries/Executables in the CMakeLists.txt

    or 
    cmake --build . --target Executable # Executable name 
    cmake --build . --target Library    # library name 
```
If you have already built the cmake project, you can update with 
```bash
    cmake .
```
This will generate executable .exe or lib(.lib/.a).  In unix one can select target as below
```bash
    cd build
    make Executable # builds only Executable 
    make Library # builds only Library
```

### Get the list of generator
It might be required for build generation
```bash
    cmake --help
```
## When Executable depends on a library (or other implementation file) in same directory 
Suppose we have an executable which depends on a library and we have segregated library and executable code in different .h/.cpp
add implementation to my_lib.h/.cpp

```bash
    #create library
    add_library(Library STATIC my_lib.cpp)

    #create executable
    add_executable(Executable main.cpp)

    #but executable depends on library therefore link the library/ies to executable
    target_link_libraries(Executable PUBLIC Library)
```

Sometimes you dont want a separate library file, you can do above in a single line if you dont want library

```bash
    add_executable(Executable 01_move_funcs_to_separate_files.cpp fun_lib.cpp)
```

## When Library code is in a separate folder (e.g. my_lib)
- Create my_lib folder and add add_subdirectory(my_lib) in CMakeLists.txt of current directory
- Go my_lib filder and create another CMakeLists.text file with below content
```bash
    add_library(Library STATIC "fun_lib.cpp")
    target_include_directories(Library PUBLIC "./") # is used for including headers
```
Note: Every sub-diretory needs to have CMakeLists.txt. If a sub directory has just folders no source files.. add list of add_subdirectory(dir_name) to CMakeLists.txt.
Executable will go to directory having file with main func

## When Headers/source files are kept in separate folder (e.g. src/ include/)
If headers/source are in separte folders say include/src folder, CMakeLists.txt from 'include' directory will have 
```bash
    target_include_directories(${LIBRARY_NAME} PUBLIC "./")
```
and  CMakeLists.txt from 'source'' will have 
```bash
    add_library(${LIBRARY_NAME} STATIC "my_lib.cc")

    #if you have executable impl file in same src folder
    add_executable({EXE_NAME} app.cpp)
    target_link_libraries({EXE_NAME} PUBLIC {LIBRARY_NAME})
```

## Add Variables to CMakeLists.txt
You can add project specific variables 
```bash
    set(EXECUTABLE_NAME Executable)
    set(LIBRARY_NAME Library)
```
You are supposed to initialize various pre-defined cpp variables

```bash
    set(CMAKE_CXX_STANDARD          17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS        OFF)
```
## Group Sources/Headers to build
Many a times we have multiple headers/source files in folder and final library or executable wants few or all of these.
```bash
    set(LIB_SRCS
            fun_lib1.cpp
            fun_lib2.cpp)

    set(LIB_HDRS
            fun_lib1.h```

            fun_lib2.h)


    add_library(${LIB_NAME} STATIC ${LIB_SRCS} ${LIB_HDRS})
    target_include_directories(${LIB_NAME} PUBLIC "./")
``` 
## Options in CMakeLists.txt

```bash
    option(COMPILE_EXECUTABLE "Whether to compile the executable" ON) 
```

How we use options:  Options can be used for conditional build
```bash
    option(COMPILE_EXECUTABLE "Whether to compile the executable" OFF)
    if (COMPILE_EXECUTABLE)
        add_subdirectory(app)
    else()
    endif()
```
You can change option by editing CMakeLists.txt or while configuring from build folder
```bash
    cd build
    # cmake -DMY_OPTION=[ON|OFF] ..
```

## How to do automatic clean of build directory (Unix only)
- create MakeFile close to CMakeLists.txt and add below bash command with target
```bash
    prepare:
        rm -rf build
        mkdir build
        cd build
```
and run from command line
```bash
    make prepare
```
## How to build in Release/Debug mode? 
```bash
    cd build
    # -D Works for variable name as well(besides options)
    cmake -DCMAKE_BUILD_TYPE=Release ..
```
Note: To debug, one can change variables/options temporarily in 'CMakeCache.txt'
you can also get these variable/options value by searching "cmake cache" in command pallete(ctrl shift p)

## How to generate automatic headers
create config.h.in (.in means file to be copied somewhere) in 'configured' folder and copy below code in 'CMakeLists.txt'. 
```bash 
    configure_file(
        "config.h.in"
        "${CMAKE_BINARY_DIR}/configured_files/include/config.h" ESCAPE_QUOTES
    )
```
On configuration, config.h.in which has content to be copied and have some text to be replaced will be resulting config.h at 
"build\configured_files\include\config.h"
Please not text between @@ to be replaced based on project detail in CMakeLists.txt
```bash
static constexpr std::int32_t project_version_major{@PROJECT_VERSION_MAJOR@};

#string between @@ to be replaced from config file
```
# How library linking works | PUBLIC/PRIVATE/INTERFACE
Suppose we have threee libraries in CMakeLists.txt
```bash
    add_library(A ...)
    add_library(B ...)
    add_library(C ...)
```
```cmake
add_library(A ...)
add_library(B ...)
add_library(C ...)
```

### PUBLIC

```cmake
target_link_libraries(A PUBLIC B)
target_link_libraries(C PUBLIC A)
```

When A links in B as *PUBLIC*, it says that A uses B in its implementation, and B is also used in A's public API. Hence, C can use B since it is part of the public API of A.

### PRIVATE

```cmake
target_link_libraries(A PRIVATE B)
target_link_libraries(C PRIVATE A)
```

When A links in B as *PRIVATE*, it is saying that A uses B in its
implementation, but B is not used in any part of A's public API. Any code
that makes calls into A would not need to refer directly to anything from
B.

### INTERFACE

```cmake
add_library(D INTERFACE)
target_include_directories(D INTERFACE {CMAKE_CURRENT_SOURCE_DIR}/include)
```

In general, used for header-only libraries.

# What are differnt Library types

A binary file that contains information about code.
A library cannot be executed on its own.
An application utilizes a library.

## Shared Libraries

- Linux: \*.so
- MacOS: \*.dylib
- Windows: \*.dll

Shared libraries reduce the amount of code that is duplicated in each program that makes use of the library, keeping the binaries small.

Shared libraries will however have a small additional cost for the execution.
In general the shared library is in the same directory as the executable.

### Static Libraries

- Linux/MacOS: *.a
- Windows: *.lib

Static libraries increase the overall size of the binary, but it means that you don't need to carry along a copy of the library that is being used.

As the code is connected at compile time there are not any additional run-time loading costs.

# Important CMake Variables for Paths

- CMAKE_SOURCE_DIR
  - Topmost folder (source directory) that contains a CMakeList.txt file.
- PROJECT_SOURCE_DIR
  - Contains the full path to the root of your project source directory.
- CMAKE_CURRENT_SOURCE_DIR
  - The directory where the currently processed CMakeLists.txt is located in.
- CMAKE_CURRENT_LIST_DIR
  - The directory of the listfile currently being processed. (for example a \*.cmake Module)
- CMAKE_MODULE_PATH
  - Tell CMake to search first in directories listed in CMAKE_MODULE_PATH when you use FIND_PACKAGE() or INCLUDE().
- CMAKE_BINARY_DIR
  - The filepath to the build directory

# Things you can set on targets

- target_link_libraries: Other targets; can also pass library names directly
- target_include_directories: Include directories
- target_compile_features: The compiler features you need activated, like cxx_std_11
- target_compile_definitions: Definitions
- target_compile_options: More general compile flags
- target_link_directories: Don’t use, give full paths instead (CMake 3.13+)
- target_link_options: General link flags (CMake 3.13+)
- target_sources: Add source files

# How to show dependencies 
```bash
    cmake .. --graphviz=graph.dot
    dot -Tpng graph.dot -o dependencyGraphImg.png
```
this will save image 

# Use External library using FetchContent
In order to use external library using FetchContent, external library should be cmakable library.
Let me use gtest library our mathproj
- Update CMakeLists.txt 
```bash
    include(FetchContent)

    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )


    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)

    # and somewhere towards end of file add below lines
    # here I am create test_mathproj file/executable to use gtest and mathlib


    enable_testing()

    add_executable(
    test_mathproj
    test_mathproj.cpp
    )
    target_link_libraries(
        test_mathproj
        GTest::gtest_main
        mathlib
    )

    include(GoogleTest)
    gtest_discover_tests(test_mathproj)
```
External libraries are cloned and build under build/_dep

Some of the steps for cmake build can be found on library documentatoin, as in case of gtest one can go refere
https://google.github.io/googletest/quickstart-cmake.html


# How to add doxygen support 

- Update your source files with doxygen comments
```bash
    /**
    * @brief Print Message for librar
    *
    */
```

- Install Doxygen
- Create Doxygen file using below commond
```bash
    doxygen -g 
```
This will create default Doxygen file .. update fields as required specially project related information and input paths and what files to scan.
(Please refer sample_Doxyfile)

You can move this Doxygen file to docs/ for better placement and run 
```bash 
    doxygen 
```
It will create a html folder in docs/. look for index.html, right click and open in default browser to see documentation

## How to automate in CMake
Create a Cmake module Docs.cmake in ./cmake with below content
```cmake
find_package(Doxygen)

if (DOXYGEN_FOUND)
    message("..............Doxygen found...............")
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        COMMENT "Generating HTML documentation with Doxygen"
    )
endif()
```
and you can use this module in CMakeLists.txt
```cmake
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
    include(Docs)
```
Now once you build app successfully. One can go to vscode command palette and search for 'Build Target' and run 'docs' target

or run custom target created in Docs.cmake from command line to generate 'html' folder. open index.html in default browser to see your documentation
```cmake 
    cmake --build . --target docs
```
