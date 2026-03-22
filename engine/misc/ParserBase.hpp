#pragma once

#include <utility/Definitions.hpp>
#include <common/TypeTraits.hpp>


namespace Kiwi::Globals::Misc {
    constexpr StringView END_OF_TOKEN = { " \n\r\0\t", 5 };
    constexpr StringView END_OF_LINE = { "\n\0", 2 };
    constexpr StringView WHITESPACE = " \t";
}


namespace Kiwi::Misc {
    class ParserBase {
    public:
        ParserBase() = default;
        explicit ParserBase(StringView src);

    public:
        void Reset(StringView src);

        KIWI_NODISCARD Opt<String> GetCurrentToken(size_t pos) const;
        KIWI_NODISCARD Opt<String> GetCurrentToken() const;
      
        KIWI_NODISCARD Opt<String> GetSequenceUpTo(size_t extremePos) const;

        KIWI_NODISCARD size_t JumpToNextLine();
        
        KIWI_NODISCARD Opt<Vector<String>> Tokenize(size_t begin, size_t end = StringView::npos, StringView delim = Globals::Misc::END_OF_TOKEN) const;
        KIWI_NODISCARD Opt<Vector<String>> Tokenize(size_t end, StringView delim = Globals::Misc::END_OF_TOKEN) const;
        KIWI_NODISCARD Opt<Vector<String>> Tokenize(StringView delim = Globals::Misc::END_OF_TOKEN) const;

    protected:
        StringView m_src;
        size_t m_currPos = 0;
    };
}