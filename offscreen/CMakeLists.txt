cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(offscreen)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPPM=1 -DLIBPNG=1 -DFFMPEG=1 -ggdb3 -std=c99 -O0 -Wall -Wextra")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} OFF_SCREEN_CPP_SOURCE)
add_executable (offscreen ${OFF_SCREEN_CPP_SOURCE})
target_link_libraries (offscreen GL GLU glut png avcodec swscale avutil)