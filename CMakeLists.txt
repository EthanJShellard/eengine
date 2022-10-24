cmake_minimum_required(VERSION 3.0)
project(EENGINE)

add_library(rend
    src/rend/rend.h
    src/rend/Animation.h
    src/rend/Animation.cpp
    src/rend/Buffer.h
    src/rend/Buffer.cpp
    src/rend/Mesh.h
    src/rend/mesh.cpp
    src/rend/Model.h
    src/rend/Model.cpp
    src/rend/ModelRenderer.h
    src/rend/ModelRenderer.cpp
    src/rend/Renderer.h
    src/rend/Renderer.cpp
    src/rend/RenderTexture.h
    src/rend/RenderTexture.cpp
    src/rend/rendmath.h
    src/rend/rendmath.cpp
    src/rend/Shader.h
    src/rend/Shader.cpp
    src/rend/stb_image.h
    src/rend/Texture.h
    src/rend/Texture.cpp
    src/rend/sys/Atomic.h
    src/rend/sys/config.h
    src/rend/sys/Exception.h
    src/rend/sys/File.h
    src/rend/sys/List.h
    src/rend/sys/Lock.h
    src/rend/sys/Mutex.h
    src/rend/sys/panic.h
    src/rend/sys/Pipe.h
    src/rend/sys/Private.h
    src/rend/sys/Ptr.h
    src/rend/sys/String.h
    src/rend/sys/ThreadPool.h
    src/rend/sys/Unique.h
    src/rend/sys/Vector.h
    src/rend/sys/Weak.h
    src/rend/sys/Zero.h
)

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
    src/eengine/components/Transform.h
    src/eengine/components/Transform.cpp
    src/eengine/Camera.h
    src/eengine/Camera.cpp
    src/eengine/Debug.h
    src/eengine/Debug.cpp
    src/eengine/Environment.h
    src/eengine/Environment.cpp
)

add_executable(game
    src/game/main.cpp
    src/game/components/Suicider.h
    src/game/components/Suicider.cpp
)

target_include_directories(rend
    PUBLIC include/common
    PUBLIC include/Windows-x64
)

target_include_directories(eengine
    PUBLIC include/Windows-x64
    PUBLIC include/common
)
target_include_directories(game
    PRIVATE src/eengine/
)

target_link_libraries(eengine
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/glew-2.1.0-x64/glew32.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2main.lib
    rend

)
target_link_libraries(game 
    eengine
)