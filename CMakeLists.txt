cmake_minimum_required(VERSION 3.0)
project(EENGINE)

add_library(eengine
    src/eengine/Core.h
    src/eengine/Core.cpp
)

add_executable(game
    src/game/main.cpp
)

include_directories(
    src/eengine/
)

target_link_libraries(game eengine)