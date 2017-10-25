cmake_minimum_required(VERSION 2.8)

# Name of the project
project(ThreadPool)

# Path for include
set(ThreadPool_headers_dir ${ThreadPool_SOURCE_DIR}/include CACHE STRING "ThreadPool headers dir")
include_directories( ${ThreadPool_SOURCE_DIR}/include )

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "${ThreadPool_SOURCE_DIR}/include")

#Tests
add_subdirectory(tests)
