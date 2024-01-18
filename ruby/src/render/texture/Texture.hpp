#pragma once

#include <utility/Definitions.hpp>
#include <SOIL/soil.h>
#include <glad/glad.h>

namespace Ruby
{
    enum TextureWrap
    {
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
        REPEAT = GL_REPEAT,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT
    };


    class Texture2D
    {
    public:
        Texture2D(void) = default;

        Texture2D(const RubyString& path, TextureWrap wrap=CLAMP_TO_EDGE);

        void LoadTexture(const RubyString& path, TextureWrap wrap=CLAMP_TO_EDGE);

        void Use(void);

        void StopUsing(void);

        GLuint GetTextureID(void) const;

    private:
        GLuint m_texture = -1;
    };
}