#include "Font.hpp"


namespace Ruby
{
// public
    Font::Font(RubyString fontName, size_t height, size_t width)
    {
        if (FT_Init_FreeType(&m_lib))
        {
            RUBY_CRITICAL("FreeType criritcal error: cannot to initialize a library");
            return;
        }

        if (FT_New_Face(m_lib, fontName.c_str(), 0, &m_face))
        {
            RUBY_ERROR("FreeType error: failed to load font {}", fontName);
            if (!TryToLoadSystemFont())
                return;
        }

        FT_Set_Pixel_Sizes(m_face, width, height);
    }

    
    Font::~Font()
    {
        FT_Done_Face(m_face);
        FT_Done_FreeType(m_lib);
    }


// private
    u16 Font::TryToLoadSystemFont(void)
    {
        RubyString sysFontsDir{ "C:\\Windows\\Fonts\\" };
        RubyVector<RubyString> sysFonts = { "arial.ttf", "times.ttf", "calibri.ttf", "verdana.ttf", "tahoma.ttf" };
        for (auto& font : sysFonts)
        {
            auto completePath = sysFontsDir + font;

            if (FT_New_Face(m_lib, completePath.c_str(), 0, &m_face)) 
            {
                RUBY_ERROR("FreeType error: failed to load system font {}", font);
            }
            else    return 0;
        }

        RUBY_CRITICAL("FreeType critical error: failed to load any font");
        return 1;
    }


    void Font::LoadCharecters(void)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (char i = 0; i < 128; i++)
        {
            if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
            {
                RUBY_ERROR("FreeType error: failed to load charecter {}({})", i, static_cast<GLuint>(i));
                continue;
            }

            TextureParams params;
            params.internalFormat = GL_RED;
            params.format = GL_RED;

            Texture2D texture;
            texture.LoadByBuffer(m_face->glyph->bitmap.width,
                        m_face->glyph->bitmap.rows,
                        m_face->glyph->bitmap.buffer,
                        params);
        

            Glyph glyph;
            glyph.textureID = texture.GetTextureID();
            glyph.width = m_face->glyph->bitmap.width;
            glyph.height = m_face->glyph->bitmap.rows;
            glyph.bearingX = m_face->glyph->bitmap_left;
            glyph.bearingY = m_face->glyph->bitmap_top;
            glyph.advance = m_face->glyph->advance.x;

            m_chars[i] = glyph;
        }
    }
}