#include <utility/EnumReflector.hpp>
#include <utility/RubyUtility.hpp>

#define ENUM_FIELD     EnumReflector::EnumField


namespace Ruby
{
    namespace Details::Enum
    {
        std::expected<i32, EnumValueParseError> getValue(cstr& str)
        {
            RubyString value;
            for (; *str != ')'; str++)
            {
                char ch = *str;
                RUBY_ASSERT_1(ch);

                if (ch == ' ')
                    continue;

                if (ch == ',')
                {
                    ++str;
                    if (value.empty())
                        break;

                    try { return std::stoi(value); }
                    catch(...) { return std::unexpected{ FAILED_TO_PARSE }; }
                }

                if (isAllowedChar(ch))
                   value.push_back(ch);
            }

            return std::unexpected{ VALUE_MISSING };
        }

        std::optional<RubyString> getField(cstr& str)
        {
            RubyString field;
            for (; *str != ')'; str++)
            {
                char ch = *str;
                RUBY_ASSERT_1(ch);

                if (ch == ' ' || ch == ',')
                    break;

                if (!isAllowedChar(ch))
                {
                    RUBY_ERROR("Details::Enum::getField() : symbol {} isn't allowed here.", ch);
                    return std::nullopt;
                }

                field.push_back(ch);
            }

            return field;
        }   
    }

    i32 ENUM_FIELD::GetValue(void) const
    { return m_reflector->m_enum.at(m_index).second; }

    RubyString ENUM_FIELD::GetFieldName(void) const
    { return m_reflector->m_enum.at(m_index).first; }

    i32 ENUM_FIELD::GetIndex(void) const
    { return m_index; }

    EnumReflector& ENUM_FIELD::GetReflector(void)
    { return *m_reflector; }

    ENUM_FIELD& ENUM_FIELD::operator++(void)
    {
        m_index = (m_index < m_reflector->Size() - 1) ? ++m_index : -1;
        return *this;
    }

    ENUM_FIELD ENUM_FIELD::operator++(int)
    {
        auto tmp = *this;
        ++(*this);

        return tmp;
    }

    bool ENUM_FIELD::operator==(const EnumField &other)
    {
        return m_index == other.m_index;
    }

    bool ENUM_FIELD::operator!=(const EnumField& other)
    { return !(*this == other); }

    bool ENUM_FIELD::IsHasValue(void) const
    { return m_index != -1; }

    ENUM_FIELD::operator bool(void) const
    { return IsHasValue();  }


    const ENUM_FIELD& ENUM_FIELD::operator*(void) const
    { return *this; }


    ENUM_FIELD::EnumField(std::shared_ptr<EnumReflector>&& reflector, i32 index) :
        m_reflector(std::move(reflector)),
        m_index(index)
    {}



    EnumReflector::EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues)
    {
        m_enumName = enumName;

        RUBY_ASSERT(*strValues == '(', 
            "EnumReflector::EnumReflector() : first symbol of strValues must be '('. Edit your code to '(__VA_ARGS__)'.");
        ++strValues;

        i32 nextValue = 0;
        while (*strValues != ')')
        {
            RUBY_ASSERT_1(*strValues);
            if (*strValues == ' ')
            {
                ++strValues;
                continue;
            }

            auto&& fieldName = Details::Enum::getField(strValues);
            auto&& fieldValue = Details::Enum::getValue(strValues);
            
            if (!fieldName ||
                (!fieldValue && fieldValue.error() == Details::Enum::FAILED_TO_PARSE))
            {
                RUBY_ERROR("EnumReflector::EnumReflector() : failed to parse specified enum.");
                return;
            }

            m_enum.emplace_back(
                std::make_pair(fieldName.value(), fieldValue.value_or(nextValue)));
            nextValue = fieldValue.value_or(nextValue) + 1;
        }
    }

    size_t EnumReflector::Size(void) const
    { return m_enum.size(); }

    ENUM_FIELD EnumReflector::At(i32 i) const
    {
        return (i < m_enum.size()) ? EnumField{ std::make_shared<EnumReflector>(*this), i } :
                                     end();
    }

    RubyString EnumReflector::GetName(void) const
    { return m_enumName; }

    ENUM_FIELD EnumReflector::GetByKey(const RubyString& key) const
    {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).first == key)
                return At(i);
        return end();
    }

    ENUM_FIELD EnumReflector::GetByValue(i32 value) const
    {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).second == value)
                return At(i);
        return end();
    }

    RUBY_NODISCARD ENUM_FIELD EnumReflector::begin(void) const
    { return At(0); }

    RUBY_NODISCARD ENUM_FIELD EnumReflector::end(void) const
    { return EnumField{}; }
}