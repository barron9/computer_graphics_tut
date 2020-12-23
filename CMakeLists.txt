#[[


cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

# Add header file
set(GLEW_H /usr/local/Cellar/glew/2.2.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)
include_directories(${GLEW_H} ${GLFW_H})

# Add target link
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

# Execute compilation command
set(SOURCE_FILES main.cpp)
add_executable(untitled main.cpp)

if (APPLE)
    target_link_libraries(untitled "-framework OpenGL")
    target_link_libraries(untitled "-framework GLUT")
endif()
]]


cmake_minimum_required(VERSION 3.13.1)
set(CMAKE_CXX_STANDARD 11)
project(untitled)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/sdl2")
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(untitled main.cpp )

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(untitled ${SDL2_LIBRARY} ${OPENGL_LIBRARIES})


