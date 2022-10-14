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

target_include_directories(eengine
    PRIVATE include/GLEW-2.1.0/
    PRIVATE include/SDL2-2.24.1/
)
target_include_directories(game
    PRIVATE src/eengine/
)

target_link_libraries(eengine
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/glew-2.1.0-x64/glew32.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2main.lib

)
target_link_libraries(game 
    eengine
)