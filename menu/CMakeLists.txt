cmake_minimum_required(VERSION 3.5.2)
project(menu)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z -Weverything -Wno-switch-enum -Wno-c++98-compat -Wno-padded")

set(SOURCE_FILES
        main.cpp
        menu.cpp
        menu.hpp)

add_executable(menu ${SOURCE_FILES})

target_link_libraries(menu sfml-window sfml-graphics sfml-system)

