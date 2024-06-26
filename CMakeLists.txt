cmake_minimum_required(VERSION 3.28)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)
include_directories(D:\\MySQL\\install\\include)  #include�ļ���λ��
link_directories(D:\\MySQL\\install\\lib) #lib�ļ���λ��
link_libraries(libmysql)  #lib��dll�ļ���
add_executable(untitled1 main.cpp
        Room.h
        Teacher.h
        "../CLion 2023.1.5/bin/mingw/lib/gcc/x86_64-w64-mingw32/13.1.0/include-fixed/NewSQL.h"
        Reservation.h)
