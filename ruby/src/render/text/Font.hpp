#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "Glyph.hpp"
#include "../texture/Texture2D.hpp"

#include <optional>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Ruby
{
    class RUBY_API Font
    {
    public:
        Font(void) = default;

        // If width set to 0 FreeType(vendor library) will automaticaly calculate the width,
        // based on given height
        Font(const RubyString& path, size_t height=50, size_t width=0);

        void LoadFont(const RubyString& name);

        void SetNewDimensions(u32 height, u32 width);

        // For now supported only English alphabet 
        // I.e.: (0 <= ch <= 127)
        std::optional<Glyph> GetGlyph(char ch) const;

        bool IsLoaded(void) const;

        ~Font();
    
    private:
        void LoadGlyphs(void);

        u16 TryToLoadSystemFont(void);

    private:
        RubyHashMap<char, Glyph> m_chars;
        RubyString fontFamily;

        FT_Library m_lib = nullptr;
        FT_Face m_face = nullptr;
    };

}
