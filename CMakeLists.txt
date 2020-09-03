cmake_minimum_required(VERSION 3.17)
project(titus)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/external/glm")
include_directories("${PROJECT_SOURCE_DIR}/external/volk")
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB MAINSOURCES src/*.cpp)
file(GLOB SUBSOURCES src/*/*.cpp)
file(GLOB SUBSUBSOURCES src/*/*/*.cpp)

set(SOURCE_FILES ${MAINSOURCES} ${SUBSOURCES} ${SUBSUBSOURCES} include/rendering/vulkan/VulkanDevice.h include/rendering/RenderComponent.h src/rendering/vulkan/VulkanDevice.cpp include/rendering/vulkan/VulkanRenderer.h include/rendering/Renderer.h src/rendering/vulkan/VulkanRenderer.cpp src/rendering/RenderSubsystem.cpp include/rendering/vulkan/VulkanUtils.h src/rendering/vulkan/VulkanUtils.cpp include/rendering/vulkan/VulkanSwapchain.h src/rendering/vulkan/VulkanSwapchain.cpp include/rendering/vulkan/managers/VulkanShaderModuleResource.h src/rendering/vulkan/managers/VulkanShaderModuleResource.cpp include/rendering/vulkan/managers/VulkanShaderModuleManager.h src/rendering/vulkan/managers/VulkanShaderModuleManager.cpp include/rendering/UiComponent.h src/rendering/RenderComponent.cpp src/rendering/UiComponent.cpp)

add_executable(titus main.cpp ${SOURCE_FILES})

add_subdirectory(external/volk)

target_link_libraries(titus ${SDL2_LIBRARIES} volk volk_headers)