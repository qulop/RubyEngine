#include <utility/EnumReflector.hpp>
#include <utility/RubyUtility.hpp>


namespace Ruby
{
    namespace Details::Enum
    {
        std::expected<i32, bool> getValue(cstr& str)
        {
            RubyString value;
            for (; *str != ')'; str++)
            {
                char ch = *str;
                RUBY_ASSERT_1(ch);

                if (ch == ' ' || ch == ',')
                {
                    if (ch == ' ')
                        continue;
                    try { return std::stoi(value); }
                    catch(...) { return true; }
                }

                if (isAllowedChar(ch))
                   value.push_back(ch);
            }

            return false;
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
                    RUBY_ERROR("Details::Enum::getField : symbol {} isn't allowed here.", ch);
                    return std::nullopt;
                }

                field.push_back(ch);
            }

            return field;
        }   
    }

    RubyString EnumField::GetEnumName(void) const
    { return m_reflector->GetName();; }

    i32 EnumField::GetValue(void) const
    { return m_reflector->At(m_index); }

    i32 EnumField::GetIndex(void) const
    { return m_index; }

    EnumReflector& EnumField::GetReflector(void)
    { return *m_reflector; }

    EnumField& EnumField::GoForward(void)
    { 
        m_index = (m_index < m_reflector->Size()) ? ++m_index : -1;
        return *this;
    }

    EnumField& EnumField::operator++(void)
    { return GoForward(); }

    bool EnumField::IsHasValue(void) const
    { return m_index != -1; }

    EnumField::operator bool(void) const
    { return IsHasValue();  }


    const EnumField& EnumField::operator*(void) const
    { return *this; }


    EnumField::EnumField(std::shared_ptr<EnumReflector>&& reflector, i32 index) :
        m_reflector(std::move(reflector)),
        m_index(index)
    {}


    EnumReflector::EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues)
    {
        m_enumName = enumName;

        RUBY_ASSERT(*strValues == '(', 
            "EnumReflector : first symbol of strValues must be '('. Edit your code to '(__VA_ARGS__)'.");
        ++strValues;

        i32 nextValue = 0;
        while (*strValues != ')')
        {
            RUBY_ASSERT_1(*strValues);
            if (*strValues == ' ')
                continue;

            auto&& fieldName = Details::Enum::getField(strValues);
            auto&& fieldValue = Details::Enum::getValue(strValues);
            
            if (!fieldName || (!fieldValue && fieldValue.error()))
            {
                RUBY_ERROR("EnumReflector : failed to parse specified enum.");
                return;
            }
    
            i32 value = (fieldValue.has_value()) ? fieldValue.value() : nextValue;
            
            m_enum.emplace_back(
                std::make_pair(fieldName.value(), value));
            nextValue = (fieldValue.has_value()) ? ++fieldValue.value() : ++nextValue;
        
            RUBY_INFO("EnumName: {}", m_enumName);
            for (auto&& [n, v] : m_enum) {
                RUBY_INFO("Field name: {}, value: {}", n, v);
            }
        }
    }

    size_t EnumReflector::Size(void) const
    { return m_enum.size(); }

    EnumField EnumReflector::At(i32 i) const
    {
        return (i < m_enum.size()) ?  EnumField{ std::make_shared<EnumReflector>(*this), i } : 
                                    EnumField{};
    }

    RubyString EnumReflector::GetName(void) const
    { return m_enumName; }

    EnumField EnumReflector::GetByKey(const RubyString& key) const
    {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).first == key)
                return At(i);
        return EnumField{};
    }

    EnumField EnumReflector::GetByValue(i32 value) const
    {
        for (i32 i = 0; i < m_enum.size(); i++)
            if (m_enum.at(i).second == value)
                return At(i);
        return EnumField{};
    }
}