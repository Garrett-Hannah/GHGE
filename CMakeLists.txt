cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
add_compile_options(-Wall -O2)

# Output all binaries to build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include GLM and other external headers
include_directories(/usr/include/glm)

# Define source directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SRC_ENGINE "${SRC_DIR}/Engine")
set(SRC_PHYSICS "${SRC_DIR}/Physics")
set(SRC_TOOLS "${SRC_DIR}/Tools")

# Gather all .cpp files
file(GLOB_RECURSE PROJECT_SOURCES
    ${SRC_ENGINE}/*.cpp
    ${SRC_PHYSICS}/*.cpp
    ${SRC_TOOLS}/*.cpp
)

# Add main executable
add_executable(my_program
    ${SRC_DIR}/main.cpp
    ${PROJECT_SOURCES}
)

# Link necessary libraries
target_link_libraries(my_program GL GLU SDL2 GLEW)

set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")

# Add test executable
add_executable(tests
	${TEST_DIR}/test.cpp
    ${PROJECT_SOURCES}
)

target_link_libraries(tests GL GLU SDL2 GLEW)

# Enable testing support
enable_testing()
add_test(NAME RunTests COMMAND tests)

