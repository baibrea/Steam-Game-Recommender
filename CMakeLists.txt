cmake_minimum_required(VERSION 3.24)
project(Steam_Game_Recommender)

set(CMAKE_CXX_STANDARD 14)

add_executable(Steam_Game_Recommender
        main.cpp game.cpp game.h extra.cpp extra.h)
