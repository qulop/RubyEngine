set(ENGINE_LIBRARY_SRC
    engine/audio/IAudioOutputStream.cpp

    engine/misc/EngineGlobalConfig.cpp
    engine/misc/Application.cpp
    engine/misc/IWindow.cpp
    engine/misc/Layer.cpp
    engine/misc/LayersStack.cpp
    engine/misc/Editor.cpp

    engine/events/EventManager.cpp

    engine/graphics/FontTTF.cpp
    engine/graphics/Text.cpp
    engine/graphics/Texture2D.cpp

    engine/platform/window/GLFWWindow.cpp

    engine/graphic_api/opengl/IndexBufferGL.cpp
    engine/graphic_api/opengl/VertexBufferGL.cpp
    engine/graphic_api/opengl/VertexArrayGL.cpp
    engine/graphic_api/opengl/ShaderGL.cpp

    engine/renderer/PreprocessorGLSL.cpp
    engine/renderer/ShaderMetaInfo.cpp
    engine/renderer/Renderer2D.cpp
    engine/renderer/RendererAPI.cpp
    engine/renderer/Shader.cpp
    engine/renderer/SpirV.cpp

    engine/sync/Mutex.cpp

    engine/types/Logger.cpp
    engine/types/File.cpp

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
        engine/win32/Win32IO.cpp
        engine/win32/audio/WaveOutAudioOutputStream.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/linux/LinuxScreen.cpp
    )
endif()

