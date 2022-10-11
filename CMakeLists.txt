cmake_minimum_required(VERSION 3.0)
project(EENGINE)

add_library(eengine
    src/eengine/eengine.h
    src/eengine/Core.h
    src/eengine/Core.cpp
    src/eengine/Entity.h
    src/eengine/Entity.cpp
    src/eengine/Component.h
    src/eengine/Component.cpp
    src/eengine/eengine_defines.h
)

add_executable(game
    src/game/main.cpp
    src/game/components/Suicider.h
    src/game/components/Suicider.cpp
)

include_directories(
    src/eengine/
)

target_link_libraries(game eengine)