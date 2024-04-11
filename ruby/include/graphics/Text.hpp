#pragma once

#include <utility/Definitions.hpp>
#include "Font.hpp"


namespace Ruby
{
    class RUBY_API Text
    {
    public:
        Text() = default;

        Text(const Font& font);

        Text(const RubyString& text, const Font& font);
        
        Text(const RubyString& text, size_t widht, size_t height, const Font& font);

        void SetDimensions(size_t width, size_t height);

        void SetText(const RubyString& text);

        void SetText(RubyString&& text);

        void Display(u32 x, u32 y);

        Text& operator=(const RubyString& msg);

        Text& operator=(RubyString&& msg);

    private:
        RubyString msg;


    };
}