#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>

#include <SOIL/soil.h>
#include <glad/glad.h>

namespace Ruby
{
    struct TextureParams
    {
        enum TextureWrap
        {
            CLAMP_TO_EDGE       = GL_CLAMP_TO_EDGE,
            CLAMP_TO_BORDER     = GL_CLAMP_TO_BORDER,
            REPEAT              = GL_REPEAT,
            MIRRORED_REPEAT     = GL_MIRRORED_REPEAT
        };

        enum TextureFilter
        {
            LINEAR              = GL_LINEAR,
            NEAREST             = GL_NEAREST   
        };


        TextureFilter filter = LINEAR;
        TextureWrap wrap = CLAMP_TO_EDGE;
    };


    class Texture2D
    {
    public:
        Texture2D(void) = default;

        Texture2D(const RubyString& path, TextureParams params={});

        void LoadByPath(const RubyString& path, TextureParams params={});

        void LoadByBuffer(u32 width, u32 height, unsigned char* buffer, TextureParams params={});

        void Use(void);

        void StopUsing(void);

        GLuint GetTextureID(void) const;


    private:
        GLuint m_texture = -1;
    };
}