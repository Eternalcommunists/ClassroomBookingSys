cmake_minimum_required(VERSION 3.28)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
include_directories(D:\\MySQL\\install\\include)  #include文件夹位置
link_directories(D:\\MySQL\\install\\lib) #lib文件夹位置
link_libraries(libmysql)  #lib下dll文件名
add_executable(untitled1 main.cpp)
