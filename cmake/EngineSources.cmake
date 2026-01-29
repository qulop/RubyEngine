set(ENGINE_LIBRARY_SRC
    engine/audio/IAudioOutputStream.cpp

    engine/memory/Memory.cpp

    engine/core/Application.cpp
    engine/core/EngineConfig.cpp
    engine/core/Engine.cpp
    engine/core/Object.cpp
    engine/core/LogSubsystem.cpp

    engine/misc/Window.cpp
    engine/misc/Layer.cpp
    engine/misc/LayersStack.cpp
    engine/misc/ParserBase.cpp
    engine/misc/WindowSubsystem.cpp

    engine/events/EventManager.cpp

    engine/graphics/FontTTF.cpp
    engine/graphics/Text.cpp
    engine/graphics/Texture2D.cpp

    engine/platform/window/GLFWWindow.cpp
    engine/platform/PlatformVars.cpp

    # --- BEGIN: OpenGL backend ---
    engine/backends/opengl/RenderContextGL.cpp
    engine/backends/opengl/GraphicObjectsFactoryGL.cpp
    engine/backends/opengl/buffers/VertexBufferGL.cpp
    engine/backends/opengl/shaders/ShaderGL.cpp
    engine/backends/opengl/shaders/ShaderCompilerGL.cpp
    engine/backends/opengl/pipeline/RenderPipelineGL.cpp
    # --- END ---

    # --- BEGIN: Vulkan backend ---
    engine/backends/vulkan/RenderContextVK.cpp
    engine/backends/vulkan/core/VulkanSubsystem.cpp
    engine/backends/vulkan/core/VulkanTypes.cpp
    engine/backends/vulkan/core/QueueFamilies.cpp
    engine/backends/vulkan/core/Device.cpp
    engine/backends/vulkan/core/SwapChain.cpp
    engine/backends/vulkan/memory/Allocator.cpp
    engine/backends/vulkan/GraphicObjectsFactoryVK.cpp
    engine/backends/vulkan/GraphicDeviceVK.cpp
    # --- END ---

    engine/profiler/EngineProfiler.cpp

    # --- BEGIN: Renderer ---
    engine/renderer/Renderer.cpp
    engine/renderer/GraphicDevice.cpp
    engine/renderer/IRenderContext.cpp
    engine/renderer/IGraphicObjectsFactory.cpp
    engine/renderer/pipeline/RenderPipeline.cpp
    engine/renderer/shaders/Shader.cpp
    engine/renderer/shaders/ShaderMetaInfo.cpp
    engine/renderer/shaders/PreprocessorGLSL.cpp
    engine/renderer/shaders/SpirV.cpp
    engine/renderer/shaders/ShaderCacheManager.cpp
    # --- END ---

    engine/sync/Mutex.cpp
    engine/sync/Thread.cpp

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
    editor/app/Editor.cpp
    editor/gui/ImGuiSubsystem.cpp
)


if(WIN32)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/backends/vulkan/core/win32/ImplWin32.cpp

        engine/win32/PlatformWin32.cpp
        engine/win32/audio/WaveOutAudioOutputStream.cpp
        engine/win32/io/SystemConsoleWin32.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/linux/LinuxScreen.cpp
    )
endif()

