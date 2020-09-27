cmake_minimum_required(VERSION 3.16.5)
project(titus)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/external/glm")
include_directories("${PROJECT_SOURCE_DIR}/external/volk")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/external/json/single_include")
include_directories("${PROJECT_SOURCE_DIR}/external/SPIRV-Reflect")

file(GLOB MAINSOURCES src/*.cpp)
file(GLOB SUBSOURCES src/*/*.cpp)
file(GLOB SUBSUBSOURCES src/*/*/*.cpp src/*/*/*/*.cpp)
file(GLOB REFLECTSOURCE external/SPIRV-Reflect/spirv_reflect.c)

set(SOURCE_FILES ${MAINSOURCES} ${SUBSOURCES} ${SUBSUBSOURCES} ${REFLECTSOURCE} include/rendering/vulkan/VulkanRenderpass.h src/rendering/vulkan/VulkanRenderpass.cpp include/rendering/vulkan/managers/VulkanDescriptorManager.h src/rendering/vulkan/managers/VulkanDescriptorManager.cpp include/utils/Hasher.h include/rendering/vulkan/VulkanPipelineLayout.h src/rendering/vulkan/VulkanPipelineLayout.cpp include/utils/VulkanUtils.h)

add_executable(titus main.cpp ${SOURCE_FILES})

add_subdirectory(external/volk)
add_subdirectory(external/SPIRV-Cross)

target_link_libraries(titus ${SDL2_LIBRARIES} volk volk_headers spirv-cross-core)