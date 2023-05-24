cmake_minimum_required(VERSION 2.8.8)
project(basic-tutorial)

function (add_subdirectory_if_exist arg)
    message(STATUS "add_subdirectory_if_exist: ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}/CMakeLists.txt")
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0})
    endif()
endfunction ()

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(BASIC_TUTORIAL_1_DIR ${CMAKE_CURRENT_SOURCE_DIR}/basic-tutorial-1)
set(BASIC_TUTORIAL_2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/basic-tutorial-2)
set(BASIC_TUTORIAL_5_DIR ${CMAKE_CURRENT_SOURCE_DIR}/basic-tutorial-5)

add_subdirectory_if_exist(basic-tutorial-1)
add_subdirectory_if_exist(basic-tutorial-2)
add_subdirectory_if_exist(basic-tutorial-5)