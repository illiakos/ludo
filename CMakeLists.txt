cmake_minimum_required(VERSION 3.10)
project(PawnGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# More explicit include directory addition
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create lists of source and header files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")


# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# More explicit target include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
)
