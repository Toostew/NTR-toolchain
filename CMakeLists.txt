cmake_minimum_required(VERSION 4.0)
project(NTR-toolchain)
set(CMAKE_CXX_STANDARD 17) #


add_executable(preprocessor
        preprocessor/src/preprocess.cpp
        preprocessor/inc/preprocess.h
        preprocessor/src/main.cpp
        preprocessor/inc/main.h)

target_include_directories(preprocessor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/preprocessor/inc)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")