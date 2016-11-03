cmake_minimum_required(VERSION 2.8)

project(snake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wno-deprecated")

include_directories(. core graphics objects objects/ai_snake)

file(GLOB SRCS
	./*.cpp
	./core/*.cpp
	./graphics/*.cpp
	./objects/*.cpp
	./objects/ai_snake/*.cpp
)
add_executable(snake ${SRCS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(snake ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
