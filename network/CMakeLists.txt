# 指定 CMake 最低版本
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

# 添加库的头文件
set(HEADERS
    src/include/networkcom.h
    src/include/tcpserver_api.h)

#debug 
message(STATUS "Sources: ${SOURCES}")

# to STATIC library .a(achive library)
# to SHARED library .so(shared object)
add_library(network_program SHARED ${SOURCES} ${HEADERS})

#cpp to exe file
#add_executable(network_program ${SOURCES})

#install .a or .so to lib, .exe to bin
install(TARGETS network_program
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#install header file to include
install(FILES src/include/networkcom.h src/include/tcpserver_api.h
        DESTINATION include)

#add h files
#PRIVATE表示这个头文件只对network_program有效，其它使用network_program的程序无效，
#public即引用这个库的程序也有效
target_include_directories(network_program 
PRIVATE src/include/private
PUBLIC src/inlucde
)

# 链接库（假设有个 mylib 库）
#target_link_libraries(network_programPRIVATE mylib) 
