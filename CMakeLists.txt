cmake_minimum_required(VERSION 3.6)
project(opengl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o tst")


set(SOURCE_FILES main.cpp )
add_executable(opengl ${SOURCE_FILES})
target_link_libraries(opengl GL)
target_link_libraries(opengl GLU)
target_link_libraries(opengl glut)
target_link_libraries(opengl m)