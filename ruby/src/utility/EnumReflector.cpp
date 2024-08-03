#include <utility/EnumReflector.hpp>
#include <utility/RubyUtility.hpp>

#define ENUM_FIELD                      EnumReflector::EnumField

namespace Ruby {
    namespace Details::Enum {
        RUBY_FORCEINLINE bool _isAllowedChar(char ch) {
            return std::isalpha(ch) || std::isdigit(ch) || ch == '_';
        }

        void _skipValueTokens(cstr& str) {
            static i32 nestingLevel = 0;
            while (true) {
                switch (*str) {
                    case '(': ++nestingLevel; break;
                    case ')': case ',': {
                        if (nestingLevel == 0)
                            return;
                        else
                            --nestingLevel;
                        break;
                    }
                }
                ++str;
            }
        }

        std::optional<RubyString> _getField(cstr& str) {
            RubyString field;
            while (true) {
                char ch = *str;
                RUBY_ASSERT_1(ch);

                if (ch == ' ' || ch == ',')
                    break;

                if (!_isAllowedChar(ch)) {
                    RUBY_ERROR("Details::Enum::_getField() : symbol {} isn't allowed here.", ch);
                    return std::nullopt;
                }

                field.push_back(ch);
                ++str;
            }

            return field;
        }
    }

    i32 ENUM_FIELD::GetValue() const {
        return m_reflector->m_enum.at(m_index).second;
    }

    RubyString ENUM_FIELD::GetFieldName() const {
        return m_reflector->m_enum.at(m_index).first;
    }

    i32 ENUM_FIELD::GetIndex() const {
        return m_index;
    }

    EnumReflector& ENUM_FIELD::GetReflector() {
        return *m_reflector;
    }

    ENUM_FIELD& ENUM_FIELD::operator++() {
        m_index = (m_index < m_reflector->Size() - 1) ? ++m_index : -1;
        return *this;
    }

    ENUM_FIELD ENUM_FIELD::operator++(int) {
        auto tmp = *this;
        ++(*this);

        return tmp;
    }

    bool ENUM_FIELD::operator==(const EnumField &other) const {
        return m_index == other.m_index;
    }

    bool ENUM_FIELD::operator!=(const EnumField& other) const {
        return !(*this == other);
    }

    bool ENUM_FIELD::IsHasValue() const {
        return m_index != -1;
    }

    ENUM_FIELD::operator bool() const {
        return IsHasValue();
    }


    const ENUM_FIELD& ENUM_FIELD::operator*() const {
        return *this;
    }


    ENUM_FIELD::EnumField(std::shared_ptr<EnumReflector>&& reflector, i32 index) :
        m_reflector(std::move(reflector)),
        m_index(index)
    {}



    EnumReflector::EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues) :
        m_enumName(enumName)
    {
        RUBY_MAYBE_UNUSED char lastChar = strValues[std::strlen(strValues) - 1];

        RUBY_ASSERT(*strValues == '(' && lastChar == ')',
            "EnumReflector::EnumReflector() : first and last symbols of strValues must be '(' and ')' respectively.");
        ++strValues;

        i32 fieldIndex = 0;
        for (; ; strValues++) {
            RUBY_ASSERT_1(*strValues);
            if (*strValues == ' ')
                continue;

            auto&& fieldName = Details::Enum::_getField(strValues);
            Details::Enum::_skipValueTokens(strValues);

            if (!fieldName)
                return;

            m_enum.emplace_back(
                std::make_pair(fieldName.value(), values[fieldIndex]));
            ++fieldIndex;

            if (*strValues == ')')
                break;
        }
    }

    size_t EnumReflector::Size() const {
        return m_enum.size();
    }

    ENUM_FIELD EnumReflector::At(i32 i) const {
        return (i < m_enum.size()) ? EnumField{ std::make_shared<EnumReflector>(*this), i } :
                                     end();
    }

    RubyString EnumReflector::GetName() const {
        return m_enumName;
    }

    ENUM_FIELD EnumReflector::GetByKey(const RubyString& key) const {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).first == key)
                return At(i);
        return end();
    }

    ENUM_FIELD EnumReflector::GetByValue(i32 value) const {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).second == value)
                return At(i);
        return end();
    }

    RUBY_NODISCARD ENUM_FIELD EnumReflector::begin() const {
        return At(0);
    }

    RUBY_NODISCARD ENUM_FIELD EnumReflector::end() const {
        return EnumField{};
    }
}