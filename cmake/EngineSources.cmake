set(ENGINE_LIBRARY_SRC
    engine/audio/IAudioOutputStream.cpp

    engine/memory/Memory.cpp

    engine/core/Application.cpp
    engine/core/EngineConfig.cpp
    engine/core/Engine.cpp

    engine/misc/Window.cpp
    engine/misc/Layer.cpp
    engine/misc/LayersStack.cpp
    engine/misc/ParserBase.cpp

    engine/events/EventManager.cpp

    engine/graphics/FontTTF.cpp
    engine/graphics/Text.cpp
    engine/graphics/Texture2D.cpp

    engine/platform/window/GLFWWindow.cpp
    engine/platform/PlatformVars.cpp

    engine/backends/opengl/GraphicObjectsFactoryGL.cpp
    engine/backends/opengl/buffers/VertexBufferGL.cpp
    engine/backends/opengl/shaders/ShaderGL.cpp
    engine/backends/opengl/shaders/ShaderCompilerGL.cpp
    engine/backends/opengl/pipeline/ContextGL.cpp
    engine/backends/opengl/pipeline/RenderPipelineGL.cpp

    engine/profiler/EngineProfiler.cpp

    engine/renderer/Renderer.cpp
    engine/renderer/GraphicDevice.cpp
    engine/renderer/IGraphicObjectsFactory.cpp
    engine/renderer/pipeline/RenderPipeline.cpp
    engine/renderer/shaders/Shader.cpp
    engine/renderer/shaders/ShaderMetaInfo.cpp
    engine/renderer/shaders/PreprocessorGLSL.cpp
    engine/renderer/shaders/SpirV.cpp
    engine/renderer/shaders/ShaderCacheManager.cpp

    engine/sync/Mutex.cpp

    engine/types/Logger.cpp
    engine/types/File.cpp
    engine/types/FileContent.cpp
    engine/types/TypeMetaInfo.cpp

    engine/utility/EnumReflector.cpp
    engine/utility/ProgramOptions.cpp
    engine/utility/Time.cpp
)

set(ENGINE_TESTS_SRC
    ruby/tests/framework/core/TestsRuntime.cpp
    ruby/tests/framework/core/Emoji.cpp
)

set(ENGINE_APPLICATION_SRC
    editor/Main.cpp
)


if(WIN32)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/win32/PlatformWin32.cpp
        engine/win32/audio/WaveOutAudioOutputStream.cpp
        engine/win32/io/SystemConsoleWin32.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/linux/LinuxScreen.cpp
    )
endif()

