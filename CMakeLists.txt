cmake_minimum_required(VERSION 3.17)
project(titus)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/external/glm")
include_directories("${PROJECT_SOURCE_DIR}/external/volk")
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB MAINSOURCES src/*.cpp)
file(GLOB SUBSOURCES src/*/*.cpp)
file(GLOB SUBSUBSOURCES src/*/*/*.cpp)

set(SOURCE_FILES ${MAINSOURCES} ${SUBSOURCES} ${SUBSUBSOURCES} include/rendering/vulkan/VulkanDevice.h include/rendering/RenderComponent.h src/rendering/vulkan/VulkanDevice.cpp include/rendering/vulkan/VulkanRenderer.h include/rendering/Renderer.h src/rendering/vulkan/VulkanRenderer.cpp src/rendering/RenderSubsystem.cpp)

add_executable(titus main.cpp ${SOURCE_FILES})

add_subdirectory(external/volk)

target_link_libraries(titus ${SDL2_LIBRARIES} volk volk_headers)