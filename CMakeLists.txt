project(tomatelo-router)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(LibOSRM REQUIRED)

add_executable(tomatelo-router src/main.cpp)

include_directories(SYSTEM ${LibOSRM_INCLUDE_DIRS})
link_directories(${LibOSRM_LIBRARY_DIRS})
target_link_libraries(tomatelo-router ${LibOSRM_LIBRARIES} ${LibOSRM_DEPENDENT_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LibOSRM_CXXFLAGS}")