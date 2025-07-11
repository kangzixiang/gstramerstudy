cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(openglshowpointcloud)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -O0 -Wall -g2 -ggdb -pthread")

find_library(PCAP_LIBRARY pcap)
message( "find pcap library: " ${PCAP_LIBRARY})
link_libraries(${PCAP_LIBRARY})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} GL_SHOW_POINT_CLOUD_CPP_SOURCE)
add_executable (openglshowpointcloud ${GL_SHOW_POINT_CLOUD_CPP_SOURCE})
target_link_libraries (openglshowpointcloud GL GLU glut)