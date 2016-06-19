cmake_minimum_required(VERSION 3.5)
project(sapper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        game.cpp
        game.hpp
        main.cpp
        menu.cpp
        menu.hpp
        board.cpp
        board.hpp
        field.hpp
        constants.hpp)

add_executable(sapper ${SOURCE_FILES})

target_link_libraries(sapper sfml-window sfml-graphics sfml-system)

