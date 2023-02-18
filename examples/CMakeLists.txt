cmake_minimum_required(VERSION 3.15)

project(ntp-examples LANGUAGES CXX)

# Add an executable target.
add_executable(${PROJECT_NAME})

# Add the source files to build.
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

# Link the executable target against the imported target.
# Must prefix the target with the namespace set during install.
target_link_libraries(${PROJECT_NAME} PUBLIC ntp)