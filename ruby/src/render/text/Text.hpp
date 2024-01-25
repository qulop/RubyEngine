#pragma once

#include <utility/Definitions.hpp>
#include "Font.hpp"


namespace Ruby
{
    class RUBY_API Text
    {
    public:
        Text(void) = default;

        Text(const Font& font);

        Text(const Font& font, const RubyString& text);
        
        Text(const Font& font, const RubyString& text, size_t widht, size_t height);

        void SetDimension(size_t width, size_t height);

        void Display(u32 x, u32 y);


    };
}