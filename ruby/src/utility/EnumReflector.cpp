#include <utility/EnumReflector.hpp>
#include <utility/RubyUtility.hpp>


namespace Ruby
{
    namespace Details::Enum
    {
        std::optional<i32> getValue(cstr strValues, i32& pos)
        {
            enum 
            {
                FIND_EQUALS_SIGN,
                FIND_VALUE
            } stage = FIND_EQUALS_SIGN;

            RubyString value;
            for (pos; strValues[pos] != ','; pos++)
            {
                char ch = strValues[pos];
                RUBY_ASSERT(ch);

                if (ch == ' ')
                    continue;

                if (stage == FIND_EQUALS_SIGN && ch == '=')
                {
                    stage = FIND_VALUE;
                    continue;
                }

                if (stage == FIND_VALUE && !std::isdigit(ch))
                {
                    RUBY_WARNING("Details::Enum::getValue : failed to parse value. Will be use nextValue + 1.");
                    return std::nullopt;
                }

                value.push_back(ch);
            }

            return std::stoi(value);
        }

        std::optional<RubyString> getField(cstr strValues, i32& pos)
        {
            RUBY_ASSERT(!std::isdigit(strValues[pos]), 
                "Details::Enum::getField : first symbol in field name cannot be a digit!");
            
            auto&& isCharAllowed = [](char ch) {
                return std::isalpha(ch) || std::isdigit(ch) || ch == '_';
            };

            RubyString field;
            for (pos; strValues[pos] != ')'; pos++)
            {
                char ch = strValues[pos];
                RUBY_ASSERT(ch);

                if (ch == ' ' || ch == ',')
                    break;

                if (!isCharAllowed(ch))
                {
                    RUBY_ERROR("Details::Enum::getField : symbol {} isn't allowed here.", ch);
                    return std::nullopt;
                }

                field.push_back(ch);
            }

            return field;
        }
    }

    // (Amy    = 1, Clara             , Vika = 100, Felix  )
    EnumReflector::EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues)
    {
        RubyHashMap<RubyString, i32> m_data;
        RubyString m_enumName = enumName;


        i32 pos = 0;
        RUBY_ASSERT(strValues[pos] == '(', 
            "EnumReflector : first symbol of strValues must be '('. Edit your code to '(__VA_ARGS__)'.");
        ++pos;

        size_t nextValue = 0;
        while (strValues[pos] != ')')
        {
            RUBY_ASSERT(strValues[pos]);
            if (strValues[pos] == ' ')
                continue;

            auto&& fieldName = Details::Enum::getField(strValues, pos);
            if (!fieldName) {}

            auto&& value = Details::Enum::getValue(strValues, pos);
    
            m_data[fieldName.value()] = (value.has_value()) ? value.value() : nextValue;
            nextValue = (value.has_value()) ? ++value.value() : ++nextValue;
        }
        
    }
}