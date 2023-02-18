cmake_minimum_required(VERSION 3.23)

project(ntp
  VERSION 0.0.1
  LANGUAGES CXX
  DESCRIPTION "Named template parameters for modern C++"
  HOMEPAGE_URL "https://github.com/yaneury/named-template-parameters.git"
)

# Only C++17 is supported.
# TODO: Enable C++11/C++14 support with necessary polyfills.
set (CMAKE_CXX_STANDARD 17)

# Add an interface library target (it will not be built directly).
add_library(${PROJECT_NAME} INTERFACE)

# Define GNU standard installation directories.
# Note: ${CMAKE_INSTALL_INCLUDEDIR}, ${CMAKE_INSTALL_LIBDIR} and
# ${CMAKE_CURRENT_LIST_DIR} etc. are defined in GNUInstallDirs
include(GNUInstallDirs)

# Sets the search paths for the include files after installation.
# This allows users to #include the library headers.
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Specify the target to install (ntp library defined above).
# Set the export name <name>-config (does not need to match target name).
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config)

# Set project options
option(NTP_BUILD_EXAMPLES "Set to ON to build examples" OFF)

# Build examples
if (NTP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
