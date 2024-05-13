#include <graphics/Font.hpp>
#include <platform/Platform.hpp>


namespace Ruby
{
    Font::Font()
    {
        FetchSystemFont("arial.ttf");
        SetNewDimensions(50, 0);
    }

    Font::Font(const RubyString& path, u32 height, u32 width)
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
            if (!FetchSystemFont(path))
                return;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void Font::SetNewDimensions(u32 width, u32 height)
    {
        RUBY_ASSERT(m_face != nullptr, "You firstly must load font(init FreeType library) before setting it's dimensions!");

        FT_Set_Pixel_Sizes(m_face, width, height);
        LoadGlyphs();

        if (m_fontFamily != m_face->family_name)
        { m_fontFamily = m_face->family_name; }
    }


    std::optional<Glyph> Font::GetGlyph(char ch) const
    {
        try
        { return m_chars.at(ch); }

        catch(std::out_of_range&)
        { return std::nullopt; }
    }


    RubyStringView Font::GetFamily() const
    { return m_fontFamily; }


    bool Font::IsLoaded() const
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


    bool Font::operator==(const Font& other)
    { return m_fontFamily == other.m_fontFamily; }

    bool Font::operator!=(const Font& other)
    { return !(*this == other); }


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
            params.glFormat = GL_RED;

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


    bool Font::FetchSystemFont(const Path& name) const
    {
//        std::filesystem::path fontsDest = (getPlatform() == PLATFORM_WINDOWS) ?
//                "C:\\Windows\\Fonts\\" : " /usr/local/share/fonts";
//
//        auto&& completePath = fontsDest / name;
//        if (FT_New_Face(m_lib, completePath.string().c_str(), 0, &m_face))
//            RUBY_ERROR("Font::FetchSystemFont() : failed to load specified font {}", name.string());
//
//        for (auto& font : std::filesystem::directory_iterator(fontsDest))
//        {
//            auto&& fontStr = font.path().string();
//
//            if (!FT_New_Face(m_lib, fontStr.c_str(), 0, &m_face))
//                return true;
//        }
//
//        RUBY_CRITICAL("Font::FetchSystemFont() : failed to load any font");
        return false;
    }
}