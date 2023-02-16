cmake_minimum_required(VERSION 3.1)

project(Labels)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(GNUInstallDirs)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

message(${CMAKE_BINARY_DIR})

add_library(labels SHARED include/labels/templates.hpp include/labels/traits.hpp)

add_executable(labels_driver main.cpp)
target_include_directories(labels_driver PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(labels_driver labels)

set_target_properties(labels PROPERTIES LINKER_LANGUAGE CXX)