cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(CMAKE_ENABLE_EXPORTS TRUE)

# Prevent build from being triggered in `CMakeLists.txt` folder
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. \nPlease create a directory and run cmake from there, passing the path to this source directory as the last argument. This process created the file `CMakeCache.txt' and the directory `CMakeFiles'. \nPlease delete them.")
endif()

# Use Release as default build type
if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Release)
endif()

# C++ requirements
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project build conf 
project(tomatelo-routing-machine)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

link_directories(${LibOSRM_LIBRARY_DIRS})

add_executable(tomatelo-routing-machine "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

find_package(LibOSRM REQUIRED)

target_link_libraries(tomatelo-routing-machine ${LibOSRM_LIBRARIES} ${LibOSRM_DEPENDENT_LIBRARIES})
include_directories(SYSTEM ${LibOSRM_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibOSRM_CXXFLAGS}")