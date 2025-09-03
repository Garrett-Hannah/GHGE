cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
add_compile_options(-Wall -O2)

# Include directories
include_directories(/usr/include/glm)

# Add source directories
set(SRC_DIRS
    src
    Tools
    Engine
    Physics
)

# Gather all .cpp files from source directories
file(GLOB_RECURSE PROJECT_SOURCES ${SRC_DIRS}/*.cpp)

# Main executable
add_executable(my_program main.cpp ${PROJECT_SOURCES})
target_link_libraries(my_program GL GLU SDL2 GLEW)

# Test executable
add_executable(tests test.cpp ${PROJECT_SOURCES})
target_link_libraries(tests GL GLU SDL2 GLEW)

# Add 'make test' support
enable_testing()
add_test(NAME RunTests COMMAND tests)

