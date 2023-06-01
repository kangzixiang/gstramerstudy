cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(range_image)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -O0 -Wall -g2 -ggdb")
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} RANGE_IMAGE_CPP_SOURCE)
add_executable (range_image ${RANGE_IMAGE_CPP_SOURCE})
target_link_libraries (range_image ${PCL_LIBRARIES})