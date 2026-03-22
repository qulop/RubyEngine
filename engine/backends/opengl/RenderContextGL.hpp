#pragma once

#include <renderer/IRenderContext.hpp>

#include <common/meta/TypeTraits.hpp>
#include <common/cast/CastTraits.hpp>


namespace Kiwi::OpenGL {
     enum class EOpenGLExtensions {
        DEBUG_OUTPUT      = KIWI_BIT(0),
        CLIP_CONTROL      = KIWI_BIT(1),
        ES2_COMPATIBILITY = KIWI_BIT(2),
        SPIRV_EXTENSIONS  = KIWI_BIT(3),
        GL_SPIRV          = KIWI_BIT(4),
    };

    struct ExtensionSupportInfo {
        String extensionName;
        bool isRequired = true;
        bool isSupported = false;
    };


    class RenderContextGL : public IRenderContext {
        KIWI_CREATE_OBJECT(RenderContextGL)

    public:
        static constexpr u32 OPENGL_MAJOR_VERSION = 4;
        static constexpr u32 OPENGL_MINOR_VERSION = 6;

    public:
        enum class EOpenGLLoaderVendor {
            GLAD, GLEW, GL3W
        };

        enum class ELoadContextError {
            LOADER_ERROR,
            UNSUPPORTED_LOADER,
            ALREADY_LOADED
        };

    public:
        RenderContextGL() = default;

    public:
        KIWI_NODISCARD bool Init() override;
        KIWI_NODISCARD EGraphicAPI GetUsedAPI() const override;

        KIWI_NODISCARD bool SetupDebugLayerCallback(const PFN_DebugCallback& debugCallback) override;

        KIWI_NODISCARD constexpr EOpenGLLoaderVendor GetLoaderVendor() const;

        KIWI_NODISCARD bool CheckExtensionForSupport(const char* ext) const;

    private:
        KIWI_NODISCARD std::expected<void, ELoadContextError> LoadContext();
        KIWI_NODISCARD String GetLoadErrorMessage(ELoadContextError error);
        void CreateExtensionsInfo();

    private:
        bool m_contextLoaded = false;
        HashMap<EOpenGLExtensions, ExtensionSupportInfo> m_extensions;
    };
}


namespace Kiwi {
    template<>
    struct CastTraits<OpenGL::EOpenGLExtensions> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToString(OpenGL::EOpenGLExtensions ext) {
            using namespace OpenGL;

            switch (ext) {
                case EOpenGLExtensions::DEBUG_OUTPUT:
                    return "GL_ARB_debug_output";
                case EOpenGLExtensions::CLIP_CONTROL:
                    return "GL_ARB_clip_control";
                case EOpenGLExtensions::ES2_COMPATIBILITY:
                    return "GL_ARB_ES2_compatibility";
                case EOpenGLExtensions::SPIRV_EXTENSIONS:
                    return "GL_ARB_spirv_extensions";
                case EOpenGLExtensions::GL_SPIRV:
                    return "GL_ARB_gl_spirv";
                default:
                    return nullopt;
            }
        }


        KIWI_NODISCARD KIWI_FORCEINLINE static Vector<OpenGL::EOpenGLExtensions> Enumerate() {
            using namespace OpenGL;

            return {
                EOpenGLExtensions::DEBUG_OUTPUT,
                EOpenGLExtensions::CLIP_CONTROL,
                EOpenGLExtensions::ES2_COMPATIBILITY,
                EOpenGLExtensions::SPIRV_EXTENSIONS,
                EOpenGLExtensions::GL_SPIRV,
            };
        }
    };
}
