cmake_minimum_required(VERSION 3.1)

project(Labels)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include(GNUInstallDirs)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

message(${CMAKE_BINARY_DIR})

add_library(libta SHARED include/template/arguments/extract.hpp include/template/arguments/traits.hpp)

add_executable(ta main.cpp)
target_include_directories(ta PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(ta libta)
set_target_properties(libta PROPERTIES LINKER_LANGUAGE CXX)
