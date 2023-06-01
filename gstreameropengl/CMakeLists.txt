cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(gstreameropengl)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -O0 -Wall -g2 -ggdb")
find_package(PkgConfig)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
include_directories(
        ${GLIB_INCLUDE_DIRS}
        ${GSTREAMER_INCLUDE_DIRS}
)
link_directories(
        ${GLIB_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
)
LINK_LIBRARIES(${GSTREAMER_LIBRARIES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} GSTREAMER_OPENGL_CPP_SOURCE)
add_executable (gstreameropengl ${GSTREAMER_OPENGL_CPP_SOURCE})
target_link_libraries (gstreameropengl ${GSTREAMER_LIBRARIES})