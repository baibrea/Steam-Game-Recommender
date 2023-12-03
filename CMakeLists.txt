cmake_minimum_required(VERSION 3.24)
project(Steam_Game_Recommender)

set(CMAKE_CXX_STANDARD 14)

add_executable(Steam_Game_Recommender
        main.cpp game.cpp game.h extra.cpp extra.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(Steam_Game_Recommender sfml-system sfml-window sfml-graphics sfml-audio)