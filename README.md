
# CMake Step by Step
## Tips

## When you have just one impl file 
```bash
cmake_minimum_required(VERSION 3.16)
project(CppCMakeLearning VERSION 1.0.0 LANGUAGES C CXX)

add_executable(Executable learning.cpp)
```
## Add impl to separate file .h/.cpp
add implementation to my_lib.h/.cpp

```bash
add_library(Library STATIC my_lib.cpp)
add_executable(Executable learning.cpp)
target_link_libraries(Executable PUBLIC Library)
```
## Move impl file group to separate folder (my_lib)
- create my_lib folder.
- go my_lib filder and create another CMakeLists.text file
    add_library(Library STATIC "fun_lib.cpp")
    target_include_directories(Library PUBLIC "./") # is used for including headers
- add add_subdirectory(lib) in CMakeLists.txt of parent directory

Note: every sub-diretory needs to have CMakeLists.txt
if a sub directory has just folders no source files.. add only add_subdirectories to CMakeLists.txt
Executable will go to directory having file with main func

if headers/source are in separte folders say include/source folder, CMakeLists.txt from include will have 
```
target_include_directories(${LIBRARY_NAME} PUBLIC "./")
```
and  CMakeLists.txt from include will have 
```
add_library(${LIBRARY_NAME} STATIC "my_lib.cc")
```


## Add Variables to CMakeLists.txt
```
set(EXECUTABLE_NAME Executable)
set(LIBRARY_NAME Library)


```
cpp variables

```
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
```
Options
```
option(COMPILE_EXECUTABLE "Whether to compile the executable" ON)
```

How we use options
```
option(COMPILE_EXECUTABLE "Whether to compile the executable" OFF)
if (COMPILE_EXECUTABLE)
    add_subdirectory(app)
else()
    message("Without exe compiling")
endif()

```
to make COMPILE_EXECUTABLE ON  we can do this while configuring from build folder
```
cd build
# cmake -DMY_OPTION=[ON|OFF] ..
cmake .. -DCOMPILE_EXECUTABLE
```

How to do automatic clean of build directory
- create MakeFile close to CMakeLists.txt and add below bash command with target
```
prepare:
	rm -rf build
	mkdir build
	cd build
```
and run 
```
make prepare
```
from command line

How to build in Release/Debug mode? 
```
cd build
# -D Works for variable name as well
cmake -DCMAKE_BUILD_TYPE=Release ..
```

CMakeCache.txt
variable values from CMakeLists.txt
change variable/option value temporarely 

you can also get these variable/options value by searching "cmake cache" in command pallete(ctrl shift p)
