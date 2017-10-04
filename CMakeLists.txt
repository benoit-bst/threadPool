cmake_minimum_required(VERSION 2.8)
project(ThreadPool)

set(MAJOR 0)
set(MINOR 1)
set(PATCH 0)
set(VERSION ${MAJOR}.${MINOR}.${PATCH})

# folder .Dicc for headers
set( ThreadPool_INCLUDE_DIR ${CMAKE_BINARY_DIR}/.ThreadPool CACHE INTERNAL "" FORCE)
file( REMOVE_RECURSE ${ThreadPool_INCLUDE_DIR})
include_directories( ${ThreadPool_INCLUDE_DIR} )

# Create linkPath with #include <ThreadPool/ThreadPool.hpp>
set(header_linkpath ${ThreadPool_INCLUDE_DIR}/ThreadPool/ThreadPool.hpp)
get_filename_component( destdir ${header_linkpath}  PATH )
file( MAKE_DIRECTORY ${destdir})
file( WRITE ${header_linkpath} "#include <${CMAKE_CURRENT_SOURCE_DIR}/src/ThreadPool.hpp>")

# Create linkPath with #include <ThreadPool/Task.hpp>
set(header_linkpath ${ThreadPool_INCLUDE_DIR}/ThreadPool/Task.hpp)
get_filename_component( destdir ${header_linkpath}  PATH )
file( MAKE_DIRECTORY ${destdir})
file( WRITE ${header_linkpath} "#include <${CMAKE_CURRENT_SOURCE_DIR}/src/Task.hpp>")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -Wextra")

SET(sources
  src/ThreadPool.cpp
)

SET(headers
  src/Task.hpp
  src/ThreadPool.hpp
)

#Tests
add_subdirectory(tests)
