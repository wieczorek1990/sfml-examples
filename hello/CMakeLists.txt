cmake_minimum_required(VERSION 3.5.2)
project(hello)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z -Weverything")

set(SOURCE_FILES
        main.cpp)

add_executable(hello ${SOURCE_FILES})

target_link_libraries(hello sfml-window sfml-graphics sfml-system)

