cmake_minimum_required(VERSION 3.10)
project(network_project)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)

# 添加可执行文件

file(GLOB_RECURSE SOURCES "src/*.cpp")
message(STATUS "Sources: ${SOURCES}")
add_executable(network_program ${SOURCES})

# 包含头文件目录
target_include_directories(network_program PRIVATE src)
