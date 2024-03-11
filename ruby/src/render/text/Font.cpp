#include <render/text/Font.hpp>


namespace Ruby
{
// public
    Font::Font(const RubyString& path, size_t height, size_t width)
    {
        LoadFont(path);

        SetNewDimensions(height, width);
    }


    void Font::LoadFont(const RubyString& path)
    {
        if (!m_lib && FT_Init_FreeType(&m_lib))
        {
                RUBY_CRITICAL("FreeType criritcal error: cannot to initialize a library");
                return;
        }

        if (FT_New_Face(m_lib, path.c_str(), 0, &m_face))
        {
            RUBY_ERROR("FreeType error: failed to load font {}", path);
            if (!TryToLoadSystemFont())
                return;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void Font::SetNewDimensions(u32 width, u32 height)
    {
        RUBY_ASSERT(m_face != nullptr && "You firstly must load font(init FreeType library) before setting it's dimensions!");

        FT_Set_Pixel_Sizes(m_face, width, height);

        LoadGlyphs();

        if (m_fontFamily != m_face->family_name)
            m_fontFamily = m_face->family_name;
    }


    std::expected<Glyph, cstr> Font::GetGlyph(char ch) const
    {
        try
        { return m_chars.at(ch); }

        catch(std::out_of_range&)
        { return std::unexprected{ "Glyph index(ch) is too big" }; }
    }


    RubyStringView Font::GetFamily(void) const
    {
        return m_fontFamily;
    }


    bool Font::IsLoaded(void) const
    {
        // m_face->family_name is <char*>
        // m_fontFamily is <RubyString>
        return (m_face && m_face->family_name == m_fontFamily);
    }

    
    Font::~Font()
    {
        FT_Done_Face(m_face);
        FT_Done_FreeType(m_lib);
    }



// private
    void Font::LoadGlyphs(void)
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


    u16 Font::TryToLoadSystemFont(void)
    {
        RubyString sysFontsDir{ "C:\\Windows\\Fonts\\" };
        RubyVector<RubyString> sysFonts = { "arial.ttf", "times.ttf", "calibri.ttf", "verdana.ttf", "tahoma.ttf" };
        for (const auto& font : sysFonts)
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
}