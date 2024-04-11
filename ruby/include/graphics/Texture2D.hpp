#pragma once

#include <utility/RubyUtility.hpp>

#include <stb_image.h>
#include <SOIL/soil.h>
#include <glad/glad.h>


namespace Ruby
{
    struct TextureParams
    {
        RUBY_ENUM_INNER(TextureWrap,
            CLAMP_TO_EDGE       = GL_CLAMP_TO_EDGE,
            CLAMP_TO_BORDER     = GL_CLAMP_TO_BORDER,
            REPEAT              = GL_REPEAT,
            MIRRORED_REPEAT     = GL_MIRRORED_REPEAT
        )

        RUBY_ENUM_INNER(TextureFilter,
            LINEAR              = GL_LINEAR,
            NEAREST             = GL_NEAREST
        )

        RUBY_ENUM_INNER(ImageFormat,
            DEFAULT             = STBI_default,
            GREY                = STBI_grey,
            GREY_ALPHA          = STBI_grey_alpha,
            RGB                 = STBI_rgb,
            RGBA                = STBI_rgb_alpha
        )


        TextureFilter filter = LINEAR;
        TextureWrap wrap = CLAMP_TO_EDGE;
        ImageFormat imageFormat = RGB;

        GLint internalFormat = GL_RGB;
        GLenum glFormat = GL_RGB;
    };


    class Texture2D
    {
    public:
        Texture2D() = default;

        explicit Texture2D(const RubyString& path, TextureParams params={});

        void LoadByPath(const RubyString& path, TextureParams params={});

        void LoadByBuffer(u32 width, u32 height, u8* buffer, TextureParams params={});

        void Use() const;

        void StopUsing() const;

        RUBY_NODISCARD GLuint GetTextureID() const;

        ~Texture2D();

    private:
        u8* m_data = nullptr;
        GLuint m_texture = -1;
    };
}