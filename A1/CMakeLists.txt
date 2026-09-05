cmake_minimum_required(VERSION 3.10)     # Ensures CMake version is recent enough
project(MTRX3760Lab2A1 CXX)              # Name of this project

set(CMAKE_CXX_STANDARD 17)               # Build against C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")     # Show warnings

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY      # Destination for generated executable
    ${CMAKE_SOURCE_DIR}/bin
)

# raylib is needed by CRender. On a machine where it was installed with apt it
# is found straight away; on a lab machine it lives in $HOME/raylib, so look
# there too (see the install notes at the top of CRender.h).
list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/raylib")
find_package(raylib REQUIRED)

# CRender and CLoopReader are shared with the rest of the labs, so they are
# used from ExampleCode rather than copied into this project.
set(EXAMPLE_CODE_DIR ${PROJECT_SOURCE_DIR}/../ExampleCode)

include_directories(                     # Where are the header files
    "${PROJECT_SOURCE_DIR}/include"
    "${EXAMPLE_CODE_DIR}"
)

add_executable( simulator                # Instructions for making "simulator"
    src/main.cpp
    src/CRobot.cpp
    src/CSimulator.cpp
    ${EXAMPLE_CODE_DIR}/CRender.cpp
    ${EXAMPLE_CODE_DIR}/CLoopReader.cpp
)

target_link_libraries( simulator         # Libraries the executable needs
    raylib
)
