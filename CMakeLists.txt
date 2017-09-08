cmake_minimum_required(VERSION 2.8)

project(snake)
add_compile_option(-Wno-deprecated)
add_compile_option(-std=c++0x)

file(GLOB SRCS ./*.cpp)
add_executable(snake ${SRCS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(snake ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
