cmake_minimum_required(VERSION 3.10.0)

# change project name depending on assignament
project(A00)
# set sources to be compiled
set (CODE Assignment0.cpp)


# ------------------------------------------------

# build to main directory to find resources
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# set c++17 that is required
set (CMAKE_CXX_STANDARD 17)

#include vulkan
find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
  message(STATUS "Vulkan found")
  include_directories(${Vulkan_INCLUDE_DIRS})
  link_libraries (${Vulkan_LIBRARIES})
endif (Vulkan_FOUND)


# include glfw
find_package(glfw3 REQUIRED)
if (glfw3_FOUND)
  message(STATUS "GLFW found")
  include_directories(${glfw3_INCLUDE_DIRS})
  link_libraries (${glfw3_LIBRARIES})
endif (glfw3_FOUND)

# include glm
find_package(glm REQUIRED)
if (glm_FOUND)
  message(STATUS "GLM found")
  include_directories(${glm_INCLUDE_DIRS})
  link_libraries (${glfm_LIBRARIES})
endif (glm_FOUND)

# add header only libraries shipped with the assignment
include_directories(headers)


# create executable
add_executable(${PROJECT_NAME}.out ${CODE}) 

# add required libraries
target_link_libraries(${PROJECT_NAME}.out dl pthread X11 Xrandr glfw)

