#include "String.hpp"

#include <common/Debug.hpp>
#include <renderer/shaders/ShaderStage.hpp>


namespace Kiwi {
    String String::EmptyString() {
        return {};
    }


    Opt<bool> String::ParseBool(StringView str) {
        auto&& strBoolEquals = [](StringView lhs, StringView rhs) -> bool {
            return std::ranges::equal(lhs, rhs, [](String::ValueType lc, String::ValueType rc) {
                return std::tolower(lc) == std::tolower(rc);
            });
        };

        if (strBoolEquals(str, "true")) {
            return true;
        }
        if (strBoolEquals(str, "false")) {
            return false;
        }

        return nullopt;
    }


    Opt<f32> String::ParseFloat(StringView str, ECharsDisplayFormat fmt)  {
        return ParseNumber<f32>(str, fmt);
    }

    Opt<f64> String::ParseDouble(StringView str, ECharsDisplayFormat fmt) {
        return ParseNumber<f64>(str, fmt);
    }

    Opt<i32> String::ParseIntI32(StringView str) {
        return ParseNumber<i32>(str);
    }

    Opt<u32> String::ParseIntU32(StringView str) {
        return ParseNumber<u32>(str);
    }

    Opt<u32> String::ParseIntI64(StringView str) {
        return ParseNumber<i64>(str);
    }
    
    
    Opt<EShaderStage> String::ParseShaderStage(StringView stageName) {
        if (stageName == "vertex") {
            return EShaderStage::VERTEX;
        }
        if (stageName == "geometry") {
            return EShaderStage::GEOMETRY;
        }
        if (stageName == "fragment") {
            return EShaderStage::FRAGMENT;
        }
        if (stageName == "compute") {
            return EShaderStage::COMPUTE;
        }

        return nullopt;
    }

    String String::FromWideString(const std::wstring& wstr) {
        return FromWideCharPtr(wstr.c_str());
    }

    String String::FromWideCharPtr(const wchar_t* cstr) {
        // size_t bytesNeeded = std::wcstombs(nullptr, cstr, 0);
        // if (bytesNeeded == static_cast<size_t>(-1)) {
        //     return {};
        // }
        //
        // String res;
        // res.ReserveSpace(bytesNeeded + 1);
        //
        // std::wcstombs(res.GetRaw(), cstr, bytesNeeded);
        return {};
    }

    index_t String::FindSubString(StringView src, StringView targetSubStr, size_t offset) {
        if (targetSubStr.empty() || src.empty()) {
            return KIWI_BAD_INDEX;
        }

        const Vector<size_t> targetSubStrPrefixes = std::move(GetPrefixVector(targetSubStr));
        index_t index = KIWI_BAD_INDEX;
        size_t j = 0;

        for (size_t i = offset; i < src.size(); i++) {
            while (j > 0 && src.at(i) != targetSubStr.at(j)) {
                j = targetSubStrPrefixes.at(j - 1);
            }

            if (src.at(i) == targetSubStr.at(j)) {
                j += 1;
            }

            if (j == targetSubStr.size()) {
                index = (i - targetSubStr.size()) + 1;
                break;
            }
        }

        return index;
    }
    
    
    String::IteratorType String::begin() {
        return m_data.begin();
    }

    String::ConstIteratorType String::begin() const {
        return m_data.begin();
    }

    String::IteratorType String::end() {
        return m_data.end();
    }

    String::ConstIteratorType String::end() const {
        return m_data.end();
    }

    String::ConstIteratorType String::cbegin() const {
        return m_data.begin();
    }

    String::ConstIteratorType String::cend() const {
        return m_data.end();
    }

    String::ReverseIteratorType String::rbegin() {
        return m_data.rbegin();
    }

    String::ConstReverseIteratorType String::rbegin() const {
        return m_data.rbegin();
    }

    String::ReverseIteratorType String::rend() {
        return m_data.rend();
    }

    String::ConstReverseIteratorType String::rend() const {
        return m_data.rend();
    }

    void String::ReserveSpace(size_t newCap) {
        m_data.reserve(newCap);
    }

    String::ValueType String::CharAt(size_t idx) const {
        return m_data.at(idx);
    }

    size_t String::IndexOf(ValueType c) const {
        return m_data.find_first_of(c);
    }

    size_t String::IndexOf(const ValueType* subStr) const {
        return m_data.find_first_of(subStr);
    }

    size_t String::IndexOf(const String& subStr) const {
        return m_data.find_first_of(subStr.m_data);
    }

    String::IteratorType String::GetIteratorByIndex(size_t idx) {
        return std::ranges::begin(m_data) + (ptrdiff_t)idx;
    }

    bool String::Contains(ValueType c) const {
        return m_data.contains(c);
    }

    bool String::Contains(const ValueType* subStr) const {
        return m_data.contains(subStr);
    }

    bool String::Contains(const String& subStr) const {
        return m_data.contains(subStr.m_data);
    }

    bool String::StartsWith(ValueType c) const {
        return m_data.starts_with(c);
    }

    bool String::StartsWith(const ValueType* subStr) const {
        return m_data.starts_with(subStr);
    }

    bool String::EndsWith(ValueType c) const {
        return m_data.ends_with(c);
    }

    bool String::EndsWith(const ValueType* subStr) const {
        return m_data.ends_with(subStr);
    }

    size_t String::Size() const noexcept {
        return m_data.size();
    }

    bool String::IsEmpty() const noexcept {
        return m_data.empty();
    }
    
    String String::CreateSlice(const size_t from, const size_t to, const size_t step) const {
        KIWI_ASSERT_BASIC(to <= Size());

        if (step == 0) {
            return EmptyString();
        }

        String res;
        res.ReserveSpace((to - from) / step);
        for (size_t i = from; i <= to; i += step) {
            res += CharAt(i);
        }
        return res;
    }

    const String::ValueType* String::ToCString() const {
        return m_data.c_str();
    }

    String::ValueType* String::GetMutableRaw() {
        return m_data.data();
    }

    Path String::ToPath() const {
        return { m_data };
    }

    StringView String::ToStringView() const {
        return StringView(m_data);
    }
    
    const std::string& String::ToStdString() const {
        return m_data;
    }

    String& String::operator=(const String& other) {
        if (&other != this) {
            m_data = other.m_data;
        }
        return *this;
    }

    String& String::operator=(String&& other) noexcept {
        if (&other != this) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    bool String::operator==(const ValueType* str) const {
        return CString::StrCmpBool(m_data.c_str(), str);
    }

    bool String::operator==(const String& other) const {
        return &other == this ? true : m_data == other.m_data;
    }

    bool String::operator!=(const ValueType* str) const {
        return !(*this == str);
    }

    bool String::operator!=(const String& other) const {
        return !(*this == other);
    }

    String& String::operator+(ValueType c) {
        m_data += c;
        return *this;
    }

    String& String::operator+(const ValueType* str) {
        m_data += str;
        return *this;
    }

    String& String::operator+(const String& other) {
        m_data += other.m_data;
        return *this;
    }

    String& String::operator+(const std::string& str) {
        m_data += str;
        return *this;
    }

    String& String::operator+=(ValueType c) {
        return operator+(c);
    }

    String& String::operator+=(const String& other) {
        return operator+(other);
    }

    String& String::operator+=(const std::string& str) {
        return operator+(str);
    }

    String& String::operator+=(const ValueType* str) {
        return operator+(str);
    }


    Vector<size_t> String::GetPrefixVector(StringView str) {
        Vector<size_t> pi(str.size(), 0);
        size_t j = 0;

        for (size_t i = 1; i < str.size(); i++) {
            while (j > 0 && str.at(i) != str.at(j)) {
                j = pi.at(j - 1);
            }

            if (str.at(i) == str.at(j)) {
                ++j;
            }

            pi[i] = j;
        }

        return pi;
    }
}
