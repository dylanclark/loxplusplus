# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

project (LoxPlusPlus)

set(APP_INC ${CMAKE_SOURCE_DIR}/src/inc)

# Include sub-projects.
add_subdirectory ("src")