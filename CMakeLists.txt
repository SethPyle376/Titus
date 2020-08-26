cmake_minimum_required(VERSION 3.17)
project(titus)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/external/glm")

add_executable(titus main.cpp src/resources/ResourceManager.cpp src/resources/TestResource.cpp include/files/FileSystem.h include/files/FilePath.h include/files/FileDriver.h include/files/Drivers/UnixFileDriver.h src/files/FileSystem.cpp include/files/FileSystemType.h include/files/File.h include/scene/Node.h src/scene/Node.cpp include/scene/Scene.h include/core/Subsystem.h include/core/testing/TestSubsystem.h include/core/testing/TestComponent.h include/core/Component.h src/core/testing/TestComponent.cpp src/core/testing/TestSubsystem.cpp)