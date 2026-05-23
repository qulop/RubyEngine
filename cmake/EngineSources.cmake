set(PCH_PATH ${CMAKE_SOURCE_DIR}/engine/common/PCH.hpp)


set(ENGINE_LIBRARY_SRC
    engine/memory/Memory.cpp

    engine/core/Application.cpp
    engine/core/EngineConfig.cpp
    engine/core/Engine.cpp
    engine/core/Object.cpp
    engine/core/LogSubsystem.cpp

    engine/misc/Window.cpp
    engine/misc/ParserBase.cpp
    engine/misc/WindowSubsystem.cpp

    engine/graphics/FontTTF.cpp
    engine/graphics/Text.cpp
    engine/graphics/Texture2D.cpp

    engine/platform/window/GLFWWindow.cpp
    engine/platform/PlatformVars.cpp

    # --- BEGIN: OpenGL backend ---
    engine/backends/opengl/RenderContextGL.cpp
    engine/backends/opengl/GraphicObjectsFactoryGL.cpp
    engine/backends/opengl/shaders/ShaderGL.cpp
    engine/backends/opengl/shaders/ShaderCompilerGL.cpp
    # --- END ---

    # --- BEGIN: Vulkan backend ---
    engine/backends/vulkan/RenderContextVK.cpp
    engine/backends/vulkan/core/VulkanSubsystem.cpp
    engine/backends/vulkan/core/VulkanTypes.cpp
    engine/backends/vulkan/core/QueueFamilies.cpp
    engine/backends/vulkan/core/Device.cpp
    engine/backends/vulkan/core/SwapChain.cpp
    engine/backends/vulkan/core/Pipeline.cpp
    engine/backends/vulkan/core/RenderPass.cpp
    engine/backends/vulkan/pipeline/RenderPipelineVK.cpp
    engine/backends/vulkan/memory/Allocator.cpp
    engine/backends/vulkan/GraphicObjectsFactoryVK.cpp
    engine/backends/vulkan/GraphicDeviceVK.cpp
    engine/backends/vulkan/shaders/ShaderCompilerVK.cpp
    engine/backends/vulkan/shaders/ShaderVK.cpp
    # --- END ---

    engine/profiler/EngineProfiler.cpp

    # --- BEGIN: Renderer ---
    engine/renderer/Renderer.cpp
    engine/renderer/IRenderContext.cpp
    engine/renderer/IGraphicObjectsFactory.cpp
    engine/renderer/pipeline/RenderPipeline.cpp
    engine/renderer/shaders/Shader.cpp
    engine/renderer/shaders/ShaderMetaInfo.cpp
    engine/renderer/shaders/PreprocessorGLSL.cpp
    engine/renderer/shaders/SpirV.cpp
    engine/renderer/shaders/ShaderCacheManager.cpp
    engine/renderer/shaders/ShaderCompiler.cpp
    # --- END ---

    engine/sync/Mutex.cpp
    engine/sync/Thread.cpp

    engine/common/filesystem/File.cpp
    engine/common/filesystem/FileContent.cpp
    engine/common/meta/TypeMetaInfo.cpp
    engine/common/Time.cpp
    engine/common/ProgramOptions.cpp
    engine/common/Debug.cpp
    engine/common/types/String.cpp
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
        engine/win32/io/SystemConsoleWin32.cpp
    )
elseif(UNIX)
    list(APPEND ENGINE_LIBRARY_SRC
        engine/linux/LinuxScreen.cpp
    )
endif()

