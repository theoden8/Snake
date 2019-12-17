cmake_minimum_required(VERSION 2.8)

project(snake)

set(RESOURCES resources)
set(ASSETS textures)
set(EXEC snake)

add_compile_options(-Wno-deprecated)
add_compile_options(-std=c++14)

file(GLOB SRCS ./*.cpp)
file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})
file(COPY tools DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(${EXEC} ${SRCS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(snake ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

if(UNIX)
  install(DIRECTORY "${ASSETS}" DESTINATION "${CMAKE_INSTALL_PREFIX}/..")
  install(DIRECTORY "${RESOURCES}" DESTINATION "${CMAKE_INSTALL_PREFIX}/..")
  install(TARGETS snake DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(DIRECTORY "${ASSETS}" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif(UNIX)
