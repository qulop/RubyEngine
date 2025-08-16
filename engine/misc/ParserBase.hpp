#pragma once

#include <utility/Definitions.hpp>
#include <types/TypeTraits.hpp>


namespace Ruby::Globals::Misc {
    constexpr StringView END_OF_TOKEN = { " \n\r\0\t", 5 };
    constexpr StringView END_OF_LINE = { "\n\0", 2 };
    constexpr StringView WHITESPACE = " \t";
}


namespace Ruby::Misc {
    class ParserBase {
    public:
        ParserBase() = default;
        explicit ParserBase(StringView src);

    public:
        void Reset(StringView src);

        RUBY_NODISCARD Opt<String> GetCurrentToken(size_t pos) const;
        RUBY_NODISCARD Opt<String> GetCurrentToken() const;
      
        RUBY_NODISCARD Opt<String> GetSequenceUpTo(size_t extremePos) const;

        RUBY_NODISCARD size_t JumpToNextLine();
        
        RUBY_NODISCARD Opt<Vector<String>> Tokenize(size_t begin, size_t end = StringView::npos, StringView delim = Globals::Misc::END_OF_TOKEN) const;
        RUBY_NODISCARD Opt<Vector<String>> Tokenize(size_t end, StringView delim = Globals::Misc::END_OF_TOKEN) const;
        RUBY_NODISCARD Opt<Vector<String>> Tokenize(StringView delim = Globals::Misc::END_OF_TOKEN) const;

    protected:
        StringView m_src;
        size_t m_currPos = 0;
    };
}