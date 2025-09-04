cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
add_compile_options(-Wall -O2)

# Output all binaries to build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Handle multi-config generators (MSVC, Xcode)
foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
endforeach()

# Include GLM and other external headers
include_directories(/usr/include/glm)

# Define source directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SRC_ENGINE "${SRC_DIR}/Engine")
set(SRC_PHYSICS "${SRC_DIR}/Physics")
set(SRC_TOOLS "${SRC_DIR}/Tools")
set(SRC_VISUAL "${SRC_DIR}/Visual")

# Gather all .cpp files
file(GLOB_RECURSE PROJECT_SOURCES
    ${SRC_ENGINE}/*.cpp
    ${SRC_PHYSICS}/*.cpp
    ${SRC_TOOLS}/*.cpp
    ${SRC_VISUAL}/*.cpp
)

# Add main executable
add_executable(my_program
    ${SRC_DIR}/main.cpp
    ${PROJECT_SOURCES}
)

target_link_libraries(my_program GL GLU SDL2 GLEW)

# Tests
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")

add_executable(tests
    ${TEST_DIR}/test.cpp
    ${PROJECT_SOURCES}
)

target_link_libraries(tests GL GLU SDL2 GLEW)

# Put both executables into build/bin explicitly
set_target_properties(my_program tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
    set_target_properties(my_program tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin
    )
endforeach()

# Enable testing support
enable_testing()

# Run tests and save output to a file
add_test(NAME RunTests
    COMMAND ${CMAKE_COMMAND} -E sh -c "$<TARGET_FILE:tests> | tee ${CMAKE_BINARY_DIR}/test_results.log"
)

