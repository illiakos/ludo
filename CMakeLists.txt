cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Project name
project(PawnGame)

# Include directories - add this BEFORE adding executables
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Collect source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(PawnGame ${SOURCES})

# Explicitly set include directories for the target
target_include_directories(PawnGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
