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

        FT_Set_Pixel_Sizes(m_face, height, width);

    }

    
    Font::~Font()
    {
        FT_Done_Face(m_face);
        FT_Done_FreeType(m_lib);
    }


// private
    uint16_t Font::TryToLoadSystemFont(void)
    {
        RubyVector<RubyString> sysFonts = { "Arial.ttf", "Times New Roman.ttf", "Calibri.ttf", "Verdana.ttf", "Terminal.ttf" };
        for (auto& i : sysFonts)
        {
            if (FT_New_Face(m_lib, i.c_str(), 0, &m_face)) 
            {
                RUBY_ERROR("FreeType error: failed to load system font {}", i);
            }
            else return 0;
        }

        RUBY_CRITICAL("FreeType critical error: failed to load any font");
        return 1;
    }


    void Font::LoadCharecters(void)
    {
        for (GLubyte i = 0; i < 128; i++)
        {
            if (FT_Load_Char(m_face, i, FT_LOAD_RENDER))
            {
                RUBY_ERROR("FreeType error: failed to load charecter {}({})", i, static_cast<GLuint>(i));
                continue;
            }

            Texture2D texture;
            texture.LoadByBuffer(m_face->glyph->bitmap.width,
                        m_face->glyph->bitmap.rows,
                        m_face->glyph->bitmap.buffer);
        

            Charecter charecter = { texture.GetTextureID(), m_face->glyph->advance.x };
            m_chars[i] = charecter;
        }
    }
}