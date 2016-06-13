cmake_minimum_required(VERSION 2.8.3)
project(test_loadLibrary)

set(CMAKE_BUILD_TYPE Debug)
message("build type: ${CMAKE_BUILD_TYPE}")

#ds output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#ds add c++11 support
add_definitions(-O0 -march=native -Wall -pedantic -std=c++11)

#ds include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)



#ds core binaries
add_executable(test_loadLibrary src/main.cpp)
target_link_libraries(test_loadLibrary -ldl)

