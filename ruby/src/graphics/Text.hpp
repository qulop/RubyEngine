#pragma once

#include <utility/Definitions.hpp>
#include "Font.hpp"


namespace Ruby {
    class RUBY_API Text {
    public:
        Text() = default;
        Text(const RubyString& text);
        Text(const Font& font);
        Text(const RubyString& text, const Font& font);
        Text(const RubyString& text, size_t widht, size_t height, const Font& font);

        void SetDimensions(size_t width, size_t height);
        void Set(const RubyString& text);

        void Display(u32 x, u32 y);

        bool operator==(const Text& other);
        bool operator!=(const Text& other);
        Text& operator=(const Text& other);
        Text& operator=(const RubyString& msg);

    private:
        RubyString m_text;
        Font m_font;
    };
}