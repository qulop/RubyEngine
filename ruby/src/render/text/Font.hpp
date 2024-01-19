#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "Char.hpp"
#include "../render/texture/Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Ruby
{

    class RUBY_API Font
    {
    public:
        Font(void) = default;

        Font(RubyString fontName, size_t height=0, size_t widt=50);

        ~Font();

    private:
        uint16_t TryToLoadSystemFont(void);

        void LoadCharecters(void);

    private:
        RubyHashMap<char, Charecter> m_chars;
        FT_Library m_lib;
        FT_Face m_face;
    };

}
