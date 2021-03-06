﻿# CMakeList.txt : CMake project for Events, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(TARGET_NAME lox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
  main.cpp)

# Add source to this project's executable.
add_executable (${TARGET_NAME} ${SOURCES})

target_precompile_headers(${TARGET_NAME} PRIVATE ${APP_INC}/loxpp_pch.h)
target_include_directories(${TARGET_NAME} PRIVATE ${APP_INC})
target_link_libraries(${TARGET_NAME}
  PUBLIC
    lox-core
)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lox)
