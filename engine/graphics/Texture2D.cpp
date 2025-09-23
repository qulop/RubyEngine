#define STB_IMAGE_IMPLEMENTATION
#include "Texture2D.hpp"

#include <utility/Assert.hpp>
#include <types/Logger.hpp>
#include <types/cast/Cast.hpp>


namespace Ruby {
    Texture2D::Texture2D(const String& path, TextureParams params) { 
        LoadByPath(path, params); 
    }


    void Texture2D::LoadByPath(const String& path, TextureParams params) {
        stbi_set_flip_vertically_on_load(true);

        i32 channels = 0;
        m_data = stbi_load(path.c_str(), &m_width, &m_height, &channels, params.imageFormat);
        if (!m_data) {
            auto&& reason = (stbi_failure_reason()) ? stbi_failure_reason() : "<unknown reason>";
            RUBY_ERROR("Texture2D::LoadByPath() : Failed to load texture from path {}. Reason: {}", path, reason);
            return;
        }

        LoadByBuffer(m_width, m_height, m_data, params);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::LoadByBuffer(i32 width, i32 height, u8* buffer, TextureParams params) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        if (TextureParams::CLAMP_TO_BORDER)
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, params.textureBorderColor.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter);

        glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, 
            width, height, 0, params.glFormat, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture2D::AddDeleter(const Deleter& deleter) { 
        m_deleter = deleter; 
    }

    const u8* Texture2D::GetData() const { 
        return m_data; 
    }

    RUBY_NODISCARD i32 Texture2D::GetWidth() const {
        return m_width;
    }

    RUBY_NODISCARD i32 Texture2D::GetHeight() const {
        return m_height;
    }

    void Texture2D::Bind() const { 
        RUBY_ASSERT(m_texture != RUBY_UNDEFINED_ID, 
            "Texture2D::Use() : You must firstly generate texture, before use it");

        glBindTexture(GL_TEXTURE_2D, m_texture); 
    }


    void Texture2D::Unbind() const { 
        RUBY_ASSERT(m_texture != RUBY_UNDEFINED_ID, 
            "Texture2D::StopUsing() : You must firstly generate texture, before call this method");

        glBindTexture(GL_TEXTURE_2D, 0); 
    }


    GLuint Texture2D::GetTextureID() const {
        RUBY_ASSERT(m_texture != RUBY_UNDEFINED_ID, 
            "Texture2D::GetTextureID() : You must firstly generate texture, before get it's id");

        return m_texture;
    }

    Texture2D::~Texture2D() {
        if (m_data)
            std::invoke(m_deleter, m_data);
        else
            RUBY_INFO("Texture2D::~Texture2D() : Nothing to free");
    }
}