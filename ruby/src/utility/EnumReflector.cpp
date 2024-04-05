// #include <utility/EnumReflector.hpp>
// #include <utility/RubyUtility.hpp>


// namespace Ruby
// {
//     namespace Details::Enum
//     {
//         bool isAllowedChar(char ch)
//         { return std::isalpha(ch) || std::isdigit(ch) || ch == '_'; }

//         std::expected<i32, bool> getValue(cstr& str)
//         {
//             RubyString value;
//             for (; *str != ')'; str++)
//             {
//                 char ch = *str;
//                 RUBY_ASSERT(ch);

//                 if (ch == ' ' || ch == ',')
//                 {
//                     if (ch == ' ')
//                         continue;
//                     try { return std::stoi(value); }
//                     catch(...) { return true; }
//                 }

//                 if (isAllowedChar(ch))
//                    value.push_back(ch);
//             }

//             return false;
//         }

//         std::optional<RubyString> getField(cstr& str)
//         {
//             RubyString field;
//             for (; *str != ')'; str++)
//             {
//                 char ch = *str;
//                 RUBY_ASSERT(ch);

//                 if (ch == ' ' || ch == ',')
//                     break;

//                 if (!isAllowedChar(ch))
//                 {
//                     RUBY_ERROR("Details::Enum::getField : symbol {} isn't allowed here.", ch);
//                     return std::nullopt;
//                 }

//                 field.push_back(ch);
//             }

//             return field;
//         }   
//     }



//     EnumReflector::EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues)
//     {
//         m_enum.enumName = enumName;

//         RUBY_ASSERT(*strValues == '(', 
//             "EnumReflector : first symbol of strValues must be '('. Edit your code to '(__VA_ARGS__)'.");
//         ++strValues;

//         size_t nextValue = 0;
//         while (*strValues != ')')
//         {
//             RUBY_ASSERT_1(*strValues);
//             if (*strValues == ' ')
//                 continue;

//             auto&& fieldName = Details::Enum::getField(strValues);
//             auto&& fieldValue = Details::Enum::getValue(strValues);
            
//             if (!fieldName || (!fieldValue && fieldValue.error()))
//             {
//                 RUBY_ERROR("EnumReflector : failed to parse specified enum.");
//                 return;
//             }
    
//             m_enum.data[fieldName.value()] = (fieldValue.has_value()) ? fieldValue.value() : nextValue;
//             nextValue = (fieldValue.has_value()) ? ++fieldValue.value() : ++nextValue;
        
//             RUBY_INFO("EnumName: {}", m_enum.enumName);
//             for (auto&& [n, v] : m_enum.data) {
//                 RUBY_INFO("Field name: {}, value: {}", n, v);
//             }
//         }
//     }
// }