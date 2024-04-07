#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby 
{
    class EnumReflector;

    namespace Details::Enum
    {
        enum EnumValueParseError
        {
            VALUE_MISSING,
            FAILED_TO_PARSE
        };

        RUBY_FORCEINLINE bool isAllowedChar(char ch)
        { return std::isalpha(ch) || std::isdigit(ch) || ch == '_'; }

        RUBY_NODISCARD std::expected<i32, EnumValueParseError> getValue(cstr& str);
        RUBY_NODISCARD std::optional<RubyString> getField(cstr& str);
    }


    class EnumReflector
    {
        using EnumType = std::vector<std::pair<RubyString, i32>>;
    public:
        class EnumField
        {
        public:
            RUBY_NODISCARD i32 GetValue(void) const;
            RUBY_NODISCARD RubyString GetFieldName(void) const;
            RUBY_NODISCARD i32 GetIndex(void) const;
            EnumReflector& GetReflector(void);

            EnumField& operator++(void);
            EnumField operator++(int);

            bool operator==(const EnumField& other);
            bool operator!=(const EnumField& other);

            operator bool(void) const;
            RUBY_NODISCARD bool IsHasValue(void) const;

            const EnumField& operator*(void) const;

        private:
            explicit EnumField(std::shared_ptr<EnumReflector>&& reflector=nullptr, i32 index=-1);

        private:
            friend class EnumReflector;

            const std::shared_ptr<EnumReflector> m_reflector = nullptr;
            i32 m_index = -1;
        };


        EnumReflector(const i32* values, i32 valuesNumber, cstr enumName, cstr strValues);
        EnumReflector(const EnumReflector& other) = default;


        template<typename EnumType>
        static EnumReflector& Create(EnumType e=EnumType{})
        { return reflectCreator(e); }

        RUBY_NODISCARD size_t Size(void) const;

        RUBY_NODISCARD RubyString GetName(void) const;

        RUBY_NODISCARD EnumField GetByKey(const RubyString& key) const;
        RUBY_NODISCARD EnumField GetByValue(i32 value) const;

        RUBY_NODISCARD EnumField At(i32 i) const;

        RUBY_NODISCARD EnumField begin(void) const;
        RUBY_NODISCARD EnumField end(void) const;

    private:
        EnumReflector(EnumReflector&& other);
        
    private:
        EnumType m_enum;
        RubyString m_enumName;
    };
}

#define RUBY_ENUM_DETAILS_namespace                                             \
        extern "C" {}                                                           \
        inline                                                                  

#define RUBY_ENUM_DETAILS_class friend                      

#define RUBY_CREATE_ENUM(enumName, EnumType, IntType, ...)                      \
    enum enumName : IntType                                                     \
    { __VA_ARGS__ };                                                            \
                                                                                \
    RUBY_ENUM_DETAILS_##EnumType Ruby::EnumReflector& reflectCreator(enumName)  \
    {                                                                           \
        static Ruby::EnumReflector reflector{ []() {                            \
            static IntType nextValue;                                           \
            nextValue = 0;                                                      \
                                                                                \
            struct Value {                                                      \
                Value(void) : val(nextValue) { nextValue += 1; }                \
                Value(int v) : val(v) { nextValue = val + 1; }                  \
                Value(const Value& other) : val(other) { nextValue = val + 1; } \
                                                                                \
                Value& operator=(const Value&) { return *this; }                \
                Value& operator=(int) { return *this; }                         \
                operator IntType() const { return val; }                        \
                IntType val;                                                    \
            } __VA_ARGS__;                                                      \
                                                                                \
            const IntType values[] = { __VA_ARGS__ };                           \
            IntType valSize = sizeof(values) / sizeof(IntType);                 \
                                                                                \
            return Ruby::EnumReflector(values,                                  \
                                       valSize,                                 \
                                       RUBY_MAKE_STRING(enumName),              \
                                       RUBY_MAKE_STRING((__VA_ARGS__)));        \
            }()                                                                 \
        };                                                                      \
                                                                                \
        return reflector;                                                       \
    }                                                                           