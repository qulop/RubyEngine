#include "Texture2D.hpp"

namespace Ruby
{
    Texture2D::Texture2D(const RubyString& path, TextureParams params)
    { LoadByPath(path, params); }


    void Texture2D::LoadByPath(const RubyString& path, TextureParams params)
    {
        int width, height;
        auto format = (params.format == GL_RGB) ? SOIL_LOAD_RGB : SOIL_LOAD_RGBA;
        unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, format);
        if (image == nullptr)
        {
            RUBY_ERROR("Failed to load texture from path {}.", path);
            return;
        }


        LoadByBuffer(width, height, image, params);

        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::LoadByBuffer(u32 width, u32 height, unsigned char* buffer, TextureParams params)
    {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter);

        glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, 
            width, height, 0, params.format, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::Use(void)
    { 
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1) 
            && "You must firstly generate texture, before use it");

        glBindTexture(GL_TEXTURE_2D, m_texture); 
    }


    void Texture2D::StopUsing(void)
    { 
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1) 
            && "You must firstly generate texture, before call this method(Texture2D::StopUsing())");

        glBindTexture(GL_TEXTURE_2D, 0); 
    }


    GLuint Texture2D::GetTextureID(void) const
    {
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1) 
            && "You must firstly generate texture, before get it's id");

        return m_texture;
    }

}