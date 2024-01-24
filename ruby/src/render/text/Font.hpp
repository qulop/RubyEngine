#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "Glyph.hpp"
#include "../render/texture/Texture2D.hpp"

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
        Font(RubyString fontName, size_t height=50, size_t width=0);

        ~Font();

    private:
        u16 TryToLoadSystemFont(void);

        void LoadCharecters(void);

    private:

        RubyHashMap<char, Glyph> m_chars;
        FT_Library m_lib;
        FT_Face m_face;
    };

}
