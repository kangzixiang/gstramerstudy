cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
 
project(basic-tutorial-6)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -O0 -Wall -g2 -ggdb")
message(${PROJECT_SOURCE_DIR})

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

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCE)
add_executable(basic-tutorial-6 ${CPP_SOURCE})

target_link_libraries(basic-tutorial-6 ${GSTREAMER_LIBRARIES})