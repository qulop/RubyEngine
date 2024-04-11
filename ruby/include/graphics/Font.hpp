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
    public:
        Font() = default;

        // If width set to 0 FreeType will automaticaly calculate the width,
        // based on given height
        Font(const RubyString& path, u32 height=50, u32 width=0);

        void LoadFont(const RubyString& name);

        void SetNewDimensions(u32 height, u32 width);

        // For now supported only English alphabet 
        // I.e.: (0 <= ch <= 127)
        std::expected<Glyph, cstr> GetGlyph(char ch) const;

        RubyStringView GetFamily() const;

        bool IsLoaded() const;

        ~Font();
    
    private:
        void LoadGlyphs();

        bool TryToLoadSystemFont();

    private:
        RubyHashMap<char, Glyph> m_chars;
        RubyString m_fontFamily;

        FT_Library m_lib = nullptr;
        FT_Face m_face = nullptr;
    };
}
