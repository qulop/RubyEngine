#include "ParserBase.hpp"


namespace Kiwi::Misc {
    ParserBase::ParserBase(StringView src) :
        m_src(src),
        m_currPos(0) 
    {}

    void ParserBase::Reset(StringView src) {
        m_src = src;
        m_currPos = 0;
    }

    Opt<String> ParserBase::GetCurrentToken(size_t pos) const {
        size_t tokenBegin = m_src.find_first_not_of(Globals::Misc::WHITESPACE, pos);
        if (tokenBegin == Kiwi::StringView::npos) {
            return Kiwi::nullopt;
        }

        size_t tokenEnd = m_src.find_first_of(Globals::Misc::END_OF_TOKEN, tokenBegin);
        if (tokenEnd == Kiwi::StringView::npos) {
            tokenEnd = m_src.size();
        }

        return Kiwi::String{ m_src.substr(tokenBegin, tokenEnd - tokenBegin) };
    }

    Opt<String> ParserBase::GetCurrentToken() const {
        return GetCurrentToken(m_currPos);
    }

    Opt<String> ParserBase::GetSequenceUpTo(size_t extremePos) const {
        if (extremePos > m_src.size()) {
            return nullopt;
        }

        return String{ m_src.substr(m_currPos, extremePos - m_currPos) };
    }

    size_t ParserBase::JumpToNextLine() {
        m_currPos = std::clamp(m_src.find_first_of('\n', m_currPos) + 1, m_currPos, m_src.size());

        return m_currPos;
    }

    KIWI_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(size_t begin, size_t end, StringView delim) const {
        if (end > m_src.size()) {
            return nullopt;
        }

        if (end == StringView::npos) {
            end = m_src.size();
        }

        Vector<String> tokens;
        size_t curr = begin;

        while (curr < end) {
            size_t next = m_src.find_first_of(delim, curr);
            if (next == StringView::npos || next > end) {
                next = end;
            }

            auto token = m_src.substr(curr, next - curr);
            if (!token.empty()) {
                tokens.emplace_back(token);
            }

            curr = next + 1;
        }

        return tokens;
    }

    KIWI_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(size_t end, StringView delim) const {
        return Tokenize(m_currPos, end, delim);
    }

    KIWI_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(StringView delim) const {
        return Tokenize(0, StringView::npos, delim);
    }

}