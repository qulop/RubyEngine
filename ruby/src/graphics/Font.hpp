#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <graphics/Texture2D.hpp>

#include <expected>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Ruby
{
    struct RUBY_API Glyph
    {
        u32 textureID;

        u32 width;
        u32 height;

        u32 bearingX;
        u32 bearingY;

        u32 advance;
    };


    class RUBY_API Font
    {
        using Path = std::filesystem::path;
    public:
        Font();
        Font(const RubyString& path, u32 height=50, u32 width=0); // If width set to 0 FreeType will automaticaly calculate the width,
                                                                  // based on given height

        void LoadFont(const RubyString& name);

        void SetNewDimensions(u32 height, u32 width);
 
        std::optional<Glyph> GetGlyph(char ch) const; // For now supported only English alphabet 
        RubyStringView GetFamily() const;

        bool IsLoaded() const;

        bool operator==(const Font& other);
        bool operator!=(const Font& other);

        ~Font();
    
    private:
        void LoadGlyphs();
        bool FetchSystemFont(const Path& name) const;

    private:
        RubyHashMap<char, Glyph> m_chars;
        RubyString m_fontFamily;

        FT_Library m_lib = nullptr;
        RubyVector<FT_Face> m_styles;
        FT_Face m_face = nullptr;
    };
}
