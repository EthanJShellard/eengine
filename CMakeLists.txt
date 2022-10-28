cmake_minimum_required(VERSION 3.0)
project(EENGINE)

find_package(OpenGL REQUIRED)

add_library(rend
    include/common/rend/rend.h
    include/common/rend/Animation.h
    include/common/rend/Animation.cpp
    include/common/rend/Buffer.h
    include/common/rend/Buffer.cpp
    include/common/rend/Mesh.h
    include/common/rend/mesh.cpp
    include/common/rend/Model.h
    include/common/rend/Model.cpp
    include/common/rend/ModelRenderer.h
    include/common/rend/ModelRenderer.cpp
    include/common/rend/Renderer.h
    include/common/rend/Renderer.cpp
    include/common/rend/RenderTexture.h
    include/common/rend/RenderTexture.cpp
    include/common/rend/rendmath.h
    include/common/rend/rendmath.cpp
    include/common/rend/Shader.h
    include/common/rend/Shader.cpp
    include/common/rend/stb_image.h
    include/common/rend/Texture.h
    include/common/rend/Texture.cpp
    include/common/rend/sys/Atomic.h
    include/common/rend/sys/config.h
    include/common/rend/sys/Exception.h
    include/common/rend/sys/File.h
    include/common/rend/sys/List.h
    include/common/rend/sys/Lock.h
    include/common/rend/sys/Mutex.h
    include/common/rend/sys/panic.h
    include/common/rend/sys/Pipe.h
    include/common/rend/sys/Private.h
    include/common/rend/sys/Ptr.h
    include/common/rend/sys/String.h
    include/common/rend/sys/ThreadPool.h
    include/common/rend/sys/Unique.h
    include/common/rend/sys/Vector.h
    include/common/rend/sys/Weak.h
    include/common/rend/sys/Zero.h
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
    src/eengine/Camera.h
    src/eengine/Camera.cpp
    src/eengine/Debug.h
    src/eengine/Debug.cpp
    src/eengine/Environment.h
    src/eengine/Environment.cpp
    src/eengine/Resources.h
    src/eengine/Resources.cpp
    src/eengine/RenderContext.h
    src/eengine/RenderContext.cpp
    src/eengine/components/Transform.h
    src/eengine/components/Transform.cpp
    src/eengine/components/QuadRenderer.h
    src/eengine/components/QuadRenderer.cpp
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

target_link_libraries(rend
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/glew-2.1.0-x64/glew32.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2.lib
    ${PROJECT_SOURCE_DIR}/lib/Windows-x64/SDL2-2.24.1/SDL2main.lib
    opengl32
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