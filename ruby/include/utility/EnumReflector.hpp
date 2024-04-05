#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


// namespace Ruby 
// {
//     namespace Details::Enum
//     {
//         struct Enumeration
//         {
//             RubyHashMap<RubyString, i32> data;
//             RubyString enumName;
//         };

//         bool isAllowedChar(char ch);

//         // In this function bool indicated presence of error. 
//         // getValue() function has three end scenario:
//         //      1) will be returned i32 (i.e. field value);
//         //      2) parser will come to end of string. In this case function will retun false, as 
//         //          no error sign.
//         //      3) function std::stoi() raise an exception and function will return true (i.e. presence of error)
//         RUBY_NODISCARD std::expected<i32, bool> getValue(cstr str, i32& pos);
//         RUBY_NODISCARD std::optional<RubyString> getField(cstr str, i32& pos);
//     }


//     class EnumReflector
//     {
//     public:
//         template<typename EnumType>
//         static EnumReflector& Create(EnumType e)
//         { return reflectCreator(e); }

//         size_t Size(void) const;






//     private:
//         EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues);
//         EnumReflector(EnumReflector&& other);

//     private:
//         Details::Enum::Enumeration m_enum;
//     };
// }

// #define RUBY_ENUM_DETAILS_namespace                                             \
//         extern "C"  {}                                                          \
//         inline   

// #define RUBY_ENUM_DETAILS_class friend                      

// #define RUBY_CREATE_ENUM(enumName, EnumType, IntType, ...)                      \
//     enum enumName : IntType                                                     \
//     {                                                                           \
//         __VA_ARGS__                                                             \
//     }                                                                           \
//                                                                                 \
//     RUBY_ENUM_DETAILS_##EnumType Ruby::EnumReflector& reflectCreator(enumName)  \
//     {                                                                           \
//         static const Ruby::EnumReflector reflector{ []() {                      \
//             static IntType nextValue;                                           \
//             nextValue = 0;                                                      \
//                                                                                 \
//             struct Value {                                                      \
//                 Value(void) : val(nextValue) { nextValue += 1; }                \
//                 Value(int v) : val(v) { nextValue = val + 1; }                  \
//                 Value(const Value& other) : val(other) { nextValue = val + 1; } \                                    \
//                                                                                 \
//                 Value& operator=(const Value&) { return *this; }                \
//                 Value& operator=(int) { return *this; }                         \
//                 operator IntType() const { return val; }                        \
//                 IntType val;                                                    \
//             } __VA_ARGS__;                                                      \
//                                                                                 \
//             const IntType values[] = { __VA_ARGS__ };                           \                   
//             size_t valSize = sizeof(values) / sizeof(IntType);                  \
//             return Ruby::EnumReflector(values, valSize,                         \ 
//                                     RUBY_MAKE_STRING(enumName),                 \ 
//                                     RUBY_MAKE_STRING((__VA_ARGS__)));           \
//             }()                                                                 \ 
//         };                                                                      \
//                                                                                 \
//         return reflector;                                                       \
//     }                                                                           