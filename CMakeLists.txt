cmake_minimum_required(VERSION 3.15)
project(rtv C)

set(CMAKE_C_STANDARD 11)
find_package(SDL2)

add_executable(rtv
        sources/main.c)

target_link_libraries(rtv -L/usr/local/lib -lSDL2)
