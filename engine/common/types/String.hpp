#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/types/CString.hpp>


namespace Kiwi {
    enum class EShaderStage : u8;
}


namespace Kiwi {
    class String final {
    public:
        using ValueType = std::string::value_type;
        using IteratorType = std::string::iterator;
        using ConstIteratorType = std::string::const_iterator;
        using ReverseIteratorType = std::string::reverse_iterator;
        using ConstReverseIteratorType = std::string::const_reverse_iterator;
    
    
        enum class ECharsDisplayFormat : u8 {
            SCIENTIFIC,
            FIXED,
            HEX,
            GENERAL,
        };
    
    public:
        KIWI_NODISCARD static String EmptyString();
    
        template<std::ranges::input_range Tx>
            requires Concepts::ConvertibleTo<std::ranges::range_value_t<Tx>, String>
        KIWI_NODISCARD static String Join(const Tx& rng, ValueType sep = ' ') {
            return std::accumulate(
                std::next(rng.begin()), rng.end(), String{ rng.front() },
                [&](String&& acc, const auto& s) {
                    return acc + sep + s;
                }
            );
        }
    
        template<Concepts::Number T>
        KIWI_NODISCARD static Opt<T> ParseNumber(StringView str, ECharsDisplayFormat fmt = ECharsDisplayFormat::GENERAL) {
            using TNumberType = std::decay_t<T>;

            std::chars_format stdCharsFormat = std::chars_format::general;
            switch (fmt) {
            case ECharsDisplayFormat::SCIENTIFIC:
                stdCharsFormat = std::chars_format::scientific; break;
            case ECharsDisplayFormat::FIXED:
                stdCharsFormat = std::chars_format::fixed; break;
            case ECharsDisplayFormat::HEX:
                stdCharsFormat = std::chars_format::hex; break;
            case ECharsDisplayFormat::GENERAL:
                stdCharsFormat = std::chars_format::general; break;
            }


            TNumberType val{ 0 };
            std::from_chars_result res{ nullptr, std::errc::invalid_argument };

            // `std::from_chars()` doesn't recognize plus sign as the first character
            const char* begin = (str.front() == '+') ? (str.data() + 1) : str.data();
            const char* end = (str.data() + str.size());

            if constexpr (std::is_integral_v<TNumberType>) {
                res = std::from_chars(begin, end, val);
            }
            else {
                res = std::from_chars(begin, end, val, stdCharsFormat);
            }

            if (res.ec != std::errc{} || res.ptr == nullptr) {
                return nullopt;
            }

            return val;
        }

        KIWI_NODISCARD static Opt<bool> ParseBool(StringView str);
    
        KIWI_NODISCARD static Opt<f32> ParseFloat(StringView str, ECharsDisplayFormat fmt = ECharsDisplayFormat::GENERAL);
    
        KIWI_NODISCARD static Opt<f64> ParseDouble(StringView str, ECharsDisplayFormat fmt = ECharsDisplayFormat::GENERAL);
    
        template<Concepts::Integral TIntType = i32>
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<TIntType> ParseInt(StringView str) {
            return ParseNumber<TIntType>(str);
        }
    
        KIWI_NODISCARD static Opt<i32> ParseIntI32(StringView str);
    
        KIWI_NODISCARD static Opt<u32> ParseIntU32(StringView str);
    
        KIWI_NODISCARD static Opt<u32> ParseIntI64(StringView str);
    
        KIWI_NODISCARD static Opt<EShaderStage> ParseShaderStage(StringView stageName);

        KIWI_NODISCARD static String FromWideString(const std::wstring& wstr);

        KIWI_NODISCARD static String FromWideCharPtr(const wchar_t* cstr);

    
        template<typename... Args>
        KIWI_NODISCARD KIWI_FORCEINLINE static String Format(std::format_string<Args...> fmt, Args&&... args) {
            return String(std::format(fmt, std::forward<Args>(args)...));
        }

        KIWI_NODISCARD static index_t FindSubString(StringView src, StringView targetSubStr, size_t offset = 0);
    
    public:
        String() = default;

        template<typename TInputIterator>
        String(TInputIterator begin, TInputIterator end) :
            m_data(begin, end)
        {}
    
        String(const ValueType* str) :
            m_data(str)
        {}
    
        String(const std::string& str) :
            m_data(str)
        {}

        String(const ValueType* str, size_t len) :
            m_data(str, len)
        {}
    
        String(std::string&& str) :
            m_data(std::move(str))
        {}

        String(std::string_view str) :
            m_data(str)
        {}

        String(const String& str) :
            m_data(str.m_data)
        {}
    
        String(String&& other) :
            m_data(std::move(other.m_data))
        {}

        KIWI_NODISCARD IteratorType begin();

        KIWI_NODISCARD ConstIteratorType begin() const;

        KIWI_NODISCARD IteratorType end();

        KIWI_NODISCARD ConstIteratorType end() const;

        KIWI_NODISCARD ConstIteratorType cbegin() const;

        KIWI_NODISCARD ConstIteratorType cend() const;

        KIWI_NODISCARD ReverseIteratorType rbegin();

        KIWI_NODISCARD ConstReverseIteratorType rbegin() const;

        KIWI_NODISCARD ReverseIteratorType rend();

        KIWI_NODISCARD ConstReverseIteratorType rend() const;

        void ReserveSpace(size_t newCap = 0);

        KIWI_NODISCARD ValueType CharAt(size_t idx) const;
    
        KIWI_NODISCARD size_t IndexOf(ValueType c) const;
    
        KIWI_NODISCARD size_t IndexOf(const ValueType* subStr) const;
    
        KIWI_NODISCARD size_t IndexOf(const String& subStr) const;
    
        KIWI_NODISCARD IteratorType GetIteratorByIndex(size_t idx);
    
        KIWI_NODISCARD bool Contains(ValueType c) const;
    
        KIWI_NODISCARD bool Contains(const ValueType* subStr) const;
    
        KIWI_NODISCARD bool Contains(const String& subStr) const;

        KIWI_NODISCARD bool StartsWith(ValueType c) const;

        KIWI_NODISCARD bool StartsWith(const ValueType* subStr) const;

        KIWI_NODISCARD bool EndsWith(ValueType c) const;

        KIWI_NODISCARD bool EndsWith(const ValueType* subStr) const;

        KIWI_NODISCARD size_t Size() const noexcept;
    
        KIWI_NODISCARD bool IsEmpty() const noexcept;


        template<Concepts::Callable TFunc>
        bool RemoveByPredicate(TFunc&& func) {
            auto&& res = std::remove_if(m_data, std::forward<TFunc>(func));

            return res != m_data.end();
        }

        KIWI_NODISCARD String CreateSlice(const size_t from, const size_t to, const size_t step = 1) const;
    
        KIWI_NODISCARD const ValueType* ToCString() const;

        KIWI_NODISCARD ValueType* GetMutableRaw();
    
        KIWI_NODISCARD Path ToPath() const;
    
        KIWI_NODISCARD StringView ToStringView() const;
        
        KIWI_NODISCARD const std::string& ToStdString() const;

        String& operator=(const String& other);
    
        String& operator=(String&& other) noexcept;
    
        bool operator==(const ValueType* str) const;
    
        bool operator==(const String& other) const;
    
        bool operator!=(const ValueType* str) const;
    
        bool operator!=(const String& other) const;
    
        String& operator+(ValueType c);

        String& operator+(const ValueType* str);

        String& operator+(const String& other);

        String& operator+(const std::string& str);

        String& operator+=(ValueType c);

        String& operator+=(const String& other);

        String& operator+=(const std::string& str);

        String& operator+=(const ValueType* str);

    private:
        KIWI_NODISCARD static Vector<size_t> GetPrefixVector(StringView str);

    private:
        std::string m_data;
    };
}


namespace Kiwi::Concepts {
    template<typename T>
    concept CanBeCastedToString = requires (T t) {
        { CastTraits<T>::ToString(t) } -> std::convertible_to<String>;
    };
}


namespace std {
    template<>
    struct formatter<Kiwi::String, Kiwi::String::ValueType> {
        constexpr auto parse(format_parse_context& ctx) {
            return ctx.begin();
        }

        auto format(const Kiwi::String& str, format_context& ctx) const {
            return format_to(ctx.out(), "{}", str.ToStringView());
        }
    };


    template<>
    struct hash<Kiwi::String> {
        std::size_t operator()(const Kiwi::String& str) const noexcept {
            return std::hash<std::string>{}(str.ToStdString());
        }
    };
}
