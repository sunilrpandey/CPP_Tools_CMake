
# CMake Step by Step

## 01. Hello CMake
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
### 02. Build and generate executable/library
Create Build directory, change directory to build and run cmake
```bash
    mkdir build
	cd build 

    cmake ..
    cmake --build . 
```
this will generate executable .exe or lib(.lib/.a)

## 03. When Executable depends on a library (or other implementation file) in same directory 
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

## 04. When Library code is in a separate folder (e.g. my_lib)
- Create my_lib folder and add add_subdirectory(my_lib) in CMakeLists.txt of current directory
- Go my_lib filder and create another CMakeLists.text file with below content
```bash
    add_library(Library STATIC "fun_lib.cpp")
    target_include_directories(Library PUBLIC "./") # is used for including headers
```
Note: Every sub-diretory needs to have CMakeLists.txt. If a sub directory has just folders no source files.. add list of add_subdirectory(dir_name) to CMakeLists.txt.
Executable will go to directory having file with main func

## 05. When Headers/source files are kept in separate folder (e.g. src/ include/)
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

## 06. Add Variables to CMakeLists.txt
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
            fun_lib1.h
            fun_lib2.h)


    add_library(${LIB_NAME} STATIC ${LIB_SRCS} ${LIB_HDRS})
    target_include_directories(${LIB_NAME} PUBLIC "./")
``` 
## 07. Options in CMakeLists.txt

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

## 08. How to do automatic clean of build directory
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
## 09. How to build in Release/Debug mode? 
```bash
    cd build
    # -D Works for variable name as well(besides options)
    cmake -DCMAKE_BUILD_TYPE=Release ..
```
Note: To debug, one can change variables/options temporarily in 'CMakeCache.txt'
you can also get these variable/options value by searching "cmake cache" in command pallete(ctrl shift p)

# 10. How to generate automatic headers
create config.h.in (.in means file to be copied somewhere) in 'configured' folder and copy 
```bash 
    configure_file(
        "config.h.in"
        "${CMAKE_BINARY_DIR}/configured_files/include/config.h" ESCAPE_QUOTES
    )
```
in 'CMakeLists.txt'. On configuration, config.h.in which has content to be copied and have some text to be replaced will be resulting config.h at 
"build\configured_files\include\config.h"
Please not text between @@ to be replaced based on project detail in CMakeLists.txt
```
    static constexpr std::int32_t project_version_major{@PROJECT_VERSION_MAJOR@};
    string between @@ to be replaced
```
