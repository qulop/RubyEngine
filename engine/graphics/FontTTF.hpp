#pragma once

#include <utility/Definitions.hpp>
#include <graphics/Texture2D.hpp>

#include <expected>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Kiwi {
    struct KIWI_API Glyph {
        u32 textureID = -1;

        u32 width = 0;
        u32 height = 0;

        u32 bearingX = 0;
        u32 bearingY = 0;

        u32 advance = 0;
    };


    class KIWI_API FontTTF {
        using Path = std::filesystem::path;
    public:
        FontTTF() = default;
        FontTTF(const String& path, u32 height=50, u32 width=0); // If width set to 0 FreeType will automaticaly calculate the width,
                                                                  // based on given height

        void LoadFontTTF(const String& name);

        void SetNewDimensions(u32 height, u32 width);
 
        KIWI_NODISCARD Opt<Glyph> GetGlyph(char ch) const; // For now supported only English alphabet
        KIWI_NODISCARD std::string_view GetFamily() const;

        bool IsLoaded() const;

        bool operator==(const FontTTF& other);
        bool operator!=(const FontTTF& other);

        ~FontTTF();
    
    private:
        void LoadGlyphs();
        bool FetchSystemFontTTF(const Path& name) const;

    private:
        HashMap<char, Glyph> m_chars;
        String m_FontTTFFamily;

        FT_Library m_lib = nullptr;
        Vector<FT_Face> m_styles;
        FT_Face m_face = nullptr;
    };
}
