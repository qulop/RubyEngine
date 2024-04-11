#include <graphics/Texture2D.hpp>

namespace Ruby
{
    Texture2D::Texture2D(const RubyString& path, TextureParams params)
    { LoadByPath(path, params); }


    void Texture2D::LoadByPath(const RubyString& path, TextureParams params)
    {
        int width, height, channels;
        u8* image = stbi_load(path.c_str(), &width, &height, &channels, params.imageFormat);
        if (!image)
        {
            auto&& reason = (stbi_failure_reason()) ? stbi_failure_reason() : std::string{};
            RUBY_ERROR("Texture2D::LoadByPath() : Failed to load texture from path {}. Reason: {}", path, reason);
            return;
        }


        LoadByBuffer(width, height, image, params);

        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::LoadByBuffer(u32 width, u32 height, u8* buffer, TextureParams params)
    {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter);

        glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, 
            width, height, 0, params.glFormat, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::Use() const
    { 
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1), 
            "Texture2D::Use() : You must firstly generate texture, before use it");

        glBindTexture(GL_TEXTURE_2D, m_texture); 
    }


    void Texture2D::StopUsing() const
    { 
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1), 
            "Texture2D::StopUsing() : You must firstly generate texture, before call this method");

        glBindTexture(GL_TEXTURE_2D, 0); 
    }


    GLuint Texture2D::GetTextureID() const
    {
        RUBY_ASSERT(m_texture != static_cast<GLuint>(-1), 
            "Texture2D::GetTextureID() : You must firstly generate texture, before get it's id");

        return m_texture;
    }

    Texture2D::~Texture2D()
    {
        if (m_data)
            stbi_image_free(m_data);
        else
            RUBY_INFO("Texture2D::~Texture2D() : Nothing to free");
    }
}