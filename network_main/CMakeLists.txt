# 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

#set project name
project(network_project_test)

# set c++ version
set(CMAKE_CXX_STANDARD 14)

#set debug
set(CMAKE_BUILD_TYPE Debug)
#set release + debug infor
#set(CMAKE_BUILD_TYPE RelWithDebInfo)

#add source file, cpp file add to parameter SOURCES
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 添加库的头文件

#debug 
message(STATUS "Sources: ${SOURCES}")

# to static library .a(achive library)
# to share library .so(shared object)
#add_library(network_program SHARE ${SOURCES} ${HEADERS})

#cpp to exe file
add_executable(network_program_test ${SOURCES})


#install header file to include

#add h files
#PRIVATE表示这个头文件只对network_program有效，其它使用network_program的程序无效，
#public即引用这个库的程序也有效

# 链接库（假设有个 mylib 库）
target_link_libraries(network_program_test PRIVATE libnetwork_program.so) 

