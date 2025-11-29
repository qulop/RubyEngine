#pragma once

#include <renderer/pipeline/RenderInstance.hpp>

#include <types/TypeTraits.hpp>
#include <types/cast/CastTraits.hpp>


namespace Ruby::OpenGL {
     enum class EOpenGLExtensions {
        DEBUG_OUTPUT      = RUBY_BIT(0),
        CLIP_CONTROL      = RUBY_BIT(1),
        ES2_COMPATIBILITY = RUBY_BIT(2),
        SPIRV_EXTENSIONS  = RUBY_BIT(3),
        GL_SPIRV          = RUBY_BIT(4),
    };

    struct ExtensionSupportInfo {
        String extensionName;
        bool isRequired = true;
        bool isSupported = false;
    };


    class ContextGL : public ARenderInstance {
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
        ContextGL() = default;

    public:
        RUBY_NODISCARD bool Init() override;
        RUBY_NODISCARD EGraphicAPI GetUsedAPI() const override;

        RUBY_NODISCARD constexpr EOpenGLLoaderVendor GetLoaderVendor() const;

        RUBY_NODISCARD bool CheckExtensionForSupport(const char* ext) const;

    private:
        RUBY_NODISCARD std::expected<void, ELoadContextError> LoadContext();
        RUBY_NODISCARD String GetLoadErrorMessage(ELoadContextError error);
        void CreateExtensionsInfo();

    private:
        bool m_contextLoaded = false;
        HashMap<EOpenGLExtensions, ExtensionSupportInfo> m_extensions;
    };
}


namespace Ruby {
    template<>
    struct CastTraits<OpenGL::EOpenGLExtensions> {
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> ToString(OpenGL::EOpenGLExtensions ext) {
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


        RUBY_NODISCARD RUBY_FORCEINLINE static Vector<OpenGL::EOpenGLExtensions> Enumerate() {
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
