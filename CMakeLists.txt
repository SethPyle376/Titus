cmake_minimum_required(VERSION 3.17)
project(titus)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include/")

add_executable(titus main.cpp src/Resources/ResourceManager.cpp src/Resources/TestResource.cpp)