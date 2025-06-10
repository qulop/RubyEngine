#pragma once

#include <utility/Definitions.hpp>

#include "TypeTraits.hpp"


namespace Ruby {
	template<typename T>
	struct BasicCString final {
	public:
		using CharType = T;
		
	public:
		BasicCString() = delete;

	public:
        RUBY_FORCEINLINE static CharType* StrCpy(CharType* dst, size_t dstsz, const CharType* src) {
            return (strcpy_s(dst, dstsz, src) == 0) ? dst : nullptr;
		}

        RUBY_FORCEINLINE static CharType* StrCpyN(CharType* dst, size_t dstsz, CharType* src, size_t count) {
            return (strncpy_s(dst, dstsz, src, count) == 0) ? dst : nullptr;
        }

        static CharType** StrArrCpy(CharType** src, size_t len, size_t offset = 0) {
            if (!src) {
                return nullptr;
            }

            size_t newLen = (len - offset) + 1;
            auto** dst = RUBY_NOTHROW_NEW CharType*[newLen];
            if (!dst) {
                return nullptr;
            }

            for (auto i = offset; i < newLen; i++) {
                CharType* dstCell = dst[i - offset];

                dstCell = RUBY_NOTHROW_NEW CharType[StrLen(src[i] + 1)];
                dstCell = StrCpy(dstCell, src[i]);
            }

            dst[newLen - 1] = nullptr;
            return dst;
        }

        RUBY_FORCEINLINE static CharType* StrCat(CharType* dst, size_t dstsz, CharType* src) {
            return (strcat_s(dst, dstsz, src) == 0) ? dst : nullptr;
        }

        RUBY_FORCEINLINE static CharType* StrCatN(CharType* dst, size_t dstsz, const CharType* src, size_t count) {
            return (strncat_s(dst, dstsz, src, count)) ? dst : nullptr;
        }

        template<typename ReturnType = size_t>
        RUBY_FORCEINLINE static ReturnType StrLen(const CharType* str) {
            return static_cast<ReturnType>(std::strlen(str));
        }

        RUBY_FORCEINLINE static i32 StrCmp(const CharType* lhs, const CharType* rhs) {
            return std::strcmp(lhs, rhs);
        }

        RUBY_FORCEINLINE static bool StrCmpBool(const CharType* lhs, const CharType* rhs) {
            return (StrCmp(lhs, rhs) == 0);
        }
	};

	class CMemoryTools {
	public:
		using RawMemoryPtr = void*;

	public:
        RUBY_FORCEINLINE static RawMemoryPtr MemSet(RawMemoryPtr dst, i32 ch, size_t count) {
			return std::memset(dst, ch, count);
		}

        RUBY_FORCEINLINE static RawMemoryPtr MemCpy(RawMemoryPtr dst, const RawMemoryPtr src, size_t count) {
			return std::memcpy(dst, src, count);
		}

        RUBY_FORCEINLINE static i32 MemCmp(const RawMemoryPtr lhs, const RawMemoryPtr rhs, size_t count) {
			return std::memcmp(lhs, rhs, count);
		}

        RUBY_FORCEINLINE static bool MemCmpBool(const RawMemoryPtr lhs, const RawMemoryPtr rhs, size_t count) {
            return (MemCmp(lhs, rhs, count) == 0);
        }
    };

	using CString = BasicCString<char>;
	//using CString16 = BasicCString<char16_t>;
	//using CString32 = BasicCString<char32_t>;

	//using CStringWide = BasicCString<wchar_t>;
}