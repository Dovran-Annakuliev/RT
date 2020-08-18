cmake_minimum_required(VERSION 3.17)
project(RTv1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework AppKit -I ~/Library/Frameworks/SDL2.framework/Headers -F /Users/ltammie/Library/Frameworks/ -framework SDL2 ")

add_executable(RTv1
        includes/rtv1.h
        sources/main.c)
