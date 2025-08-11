#include "ParserBase.hpp"


namespace Ruby::Misc {
    ParserBase::ParserBase(StringView src) :
        m_src(src),
        m_currPos(0) 
    {}

    void ParserBase::Reset(StringView src) {
        m_src = src;
        m_currPos = 0;
    }

    Opt<String> ParserBase::GetCurrentToken(size_t pos) {
        size_t tokenEnd = m_src.find_first_of(Globals::Misc::END_OF_TOKEN, pos);
        if (tokenEnd == Ruby::StringView::npos) {
            return Ruby::nullopt;
        }

        return Ruby::String{ m_src.substr(pos, tokenEnd - pos) };
    }

    Opt<String> ParserBase::GetCurrentToken() {
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

    RUBY_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(size_t begin, size_t end, StringView delim) const {
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

    RUBY_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(size_t end, StringView delim) const {
        return Tokenize(m_currPos, end, delim);
    }

    RUBY_NODISCARD Opt<Vector<String>> ParserBase::Tokenize(StringView delim) const {
        return Tokenize(0, StringView::npos, delim);
    }

}