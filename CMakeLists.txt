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
    src/eengine/NonCopyable.h
    src/eengine/Input.h
    src/eengine/Input.cpp
    src/eengine/Transform.h
    src/eengine/Transform.cpp
    src/eengine/erenderer/VertexArray.h
    src/eengine/erenderer/VertexArray.cpp
    src/eengine/erenderer/VertexBuffer.h
    src/eengine/erenderer/VertexBuffer.cpp
    src/eengine/erenderer/Shader.h
    src/eengine/erenderer/Shader.cpp
)

add_executable(game
    src/game/main.cpp
    src/game/components/Suicider.h
    src/game/components/Suicider.cpp
)

target_include_directories(eengine
    PRIVATE include/Windows-x64
    PRIVATE include/common
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