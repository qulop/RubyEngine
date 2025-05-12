set(ENGINE_LIBRARY_SRC
    ruby/src/audio/IAudioOutputStream.cpp

    ruby/src/core/EngineGlobalConfig.cpp
    ruby/src/core/Application.cpp
    ruby/src/core/IWindow.cpp
    ruby/src/core/Layer.cpp
    ruby/src/core/LayersStack.cpp
    ruby/src/core/Editor.cpp

    ruby/src/events/EventManager.cpp

    ruby/src/graphics/FontTTF.cpp
    ruby/src/graphics/Text.cpp
    ruby/src/graphics/Texture2D.cpp
    ruby/src/graphics/Color.cpp

    ruby/src/memory/Memory.cpp
    ruby/src/memory/PoolAllocator.cpp

    ruby/src/platform/GLFWWindow.cpp

    ruby/src/renderer/Buffers.cpp
    ruby/src/renderer/VertexArray.cpp
    ruby/src/renderer/ShaderDataTypes.cpp
    ruby/src/renderer/Shader.cpp
    ruby/src/renderer/Renderer.cpp
    ruby/src/renderer/RendererAPI.cpp

    ruby/src/sync/Mutex.cpp

    ruby/src/types/Logger.cpp
    ruby/src/types/File.cpp

    ruby/src/utility/EnumReflector.cpp
    ruby/src/utility/ProgramOptions.cpp
)

set(ENGINE_TESTS_SRC
    ruby/tests/framework/core/TestsRuntime.cpp
    ruby/tests/framework/core/Emoji.cpp
)

set(ENGINE_APPLICATION_SRC
    ruby/Main.cpp
)


if(WIN32)
    list(APPEND ENGINE_LIBRARY_SRC
        ruby/src/platform/win32/Win32.cpp
        ruby/src/platform/win32/api_impl/Locale.cpp
        ruby/src/platform/win32/api_impl/Memory.cpp
        ruby/src/platform/win32/audio/WaveOutAudioOutputStream.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        ruby/src/platform/linux/Linux.cpp
    )
endif()

