cmake_minimum_required(VERSION 3.10)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(game 
    src/main.cpp 
    src/Game.cpp 
    src/Player.cpp
    src/Enemy.cpp
)

target_link_libraries(game sfml-graphics sfml-window sfml-system)
