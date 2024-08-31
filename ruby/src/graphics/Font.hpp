#pragma once

#include <utility/Definitions.hpp>
#include <types/Logger.hpp>
#include <graphics/Texture2D.hpp>

#include <expected>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Ruby {
    struct RUBY_API Glyph {
        u32 textureID = -1;

        u32 width = 0;
        u32 height = 0;

        u32 bearingX = 0;
        u32 bearingY = 0;

        u32 advance = 0;
    };


    class RUBY_API Font {
        using Path = std::filesystem::path;
    public:
        Font();
        Font(const RubyString& path, u32 height=50, u32 width=0); // If width set to 0 FreeType will automaticaly calculate the width,
                                                                  // based on given height

        void LoadFont(const RubyString& name);

        void SetNewDimensions(u32 height, u32 width);
 
        Opt<Glyph> GetGlyph(char ch) const; // For now supported only English alphabet 
        std::string_view GetFamily() const;

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
