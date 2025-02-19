cmake_minimum_required(VERSION 3.10)
#set project name
project(network_project)

# set c++ version
set(CMAKE_CXX_STANDARD 14)

#set debug
set(CMAKE_BUILD_TYPE Debug)
#set release + debug infor
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

#add source file, cpp file add to parameter SOURCES
file(GLOB_RECURSE SOURCES "src/*.cpp")

#debug 
message(STATUS "Sources: ${SOURCES}")

#cpp to exe file
add_executable(network_program ${SOURCES})

#add h files
target_include_directories(network_program PRIVATE src)
