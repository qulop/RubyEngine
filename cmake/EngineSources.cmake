set(ENGINE_LIBRARY_SRC
    engine/audio/IAudioOutputStream.cpp

    engine/misc/EngineGlobalConfig.cpp
    engine/misc/Application.cpp
    engine/misc/IWindow.cpp
    engine/misc/Layer.cpp
    engine/misc/LayersStack.cpp
    engine/misc/Editor.cpp
    engine/misc/ParserBase.cpp

    engine/events/EventManager.cpp

    engine/graphics/FontTTF.cpp
    engine/graphics/Text.cpp
    engine/graphics/Texture2D.cpp

    engine/platform/window/GLFWWindow.cpp

    engine/backends/opengl/IndexBufferGL.cpp
    engine/backends/opengl/VertexBufferGL.cpp
    engine/backends/opengl/VertexArrayGL.cpp
    engine/backends/opengl/ShaderGL.cpp
    engine/backends/opengl/ShaderCompilerGL.cpp

    engine/renderer/Renderer2D.cpp
    engine/renderer/RendererAPI.cpp
    engine/renderer/shaders/Shader.cpp
    engine/renderer/shaders/ShaderMetaInfo.cpp
    engine/renderer/shaders/PreprocessorGLSL.cpp
    engine/renderer/shaders/SpirV.cpp
    engine/renderer/shaders/ShaderCacheManager.cpp

    engine/sync/Mutex.cpp

    engine/types/Logger.cpp
    engine/types/File.cpp
    engine/types/FileContent.cpp

    engine/utility/EnumReflector.cpp
    engine/utility/ProgramOptions.cpp
)

set(ENGINE_TESTS_SRC
    ruby/tests/framework/core/TestsRuntime.cpp
    ruby/tests/framework/core/Emoji.cpp
)

set(ENGINE_APPLICATION_SRC
    engine/Main.cpp
)


if(WIN32)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/win32/Win32Utils.cpp
        engine/win32/Win32Locale.cpp
        engine/win32/Win32Memory.cpp
        engine/win32/Win32Screen.cpp
        engine/win32/audio/WaveOutAudioOutputStream.cpp
        engine/win32/io/Win32SystemConsole.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/linux/LinuxScreen.cpp
    )
endif()

