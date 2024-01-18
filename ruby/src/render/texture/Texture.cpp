#include "Texture.hpp"

namespace Ruby
{
    Texture2D::Texture2D(const RubyString& path, TextureWrap wrap)
    {
        LoadTexture(path, wrap);
    }


    void Texture2D::LoadTexture(const RubyString& path, TextureWrap wrap)
    {
        int width, height;
        unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::Use(void)
    { glBindTexture(GL_TEXTURE_2D, m_texture); }


    void Texture2D::StopUsing(void)
    { glBindTexture(GL_TEXTURE_2D, 0); }


    GLuint Texture2D::GetTextureID(void) const
    {
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1) && "You must firstly generate texture, before get it's id");

        return m_texture;
    }
}