#pragma once

#include "TypeTraits.hpp"


namespace Ruby {
	template<typename CharType>
	class BasicCString final {
	public:
		using CharType = CharType;
		using NullType = std::nullptr_t;
		
	public:
		BasicCString() = delete;

	public:
		static RUBY_FORCEINLINE CharType* StrCpy(CharType* dst, CharType* src) {
			return std::strcpy_s(dst, src);
		}

		static RUBY_FORCEINLINE CharType* StrCpyN(CharType* dst, CharType* src, size_t count) {
			return std::strncpy_s(dst, src, count);
		}

		static CharType** StrArrCpy(CharType** src, size_t len, size_t offset = 0) {
			if (!src) {
				return NullType;
			}

			size_t newLen = (len - offset) + 1;
			auto** dst = RUBY_NOTHROW_NEW CharType*[newLen];
			if (!dst) {
				return NullType;
			}

			for (auto i = offset; i < newLen; i++) {
				CharType* dstCell = dst[i - offset];

				dstCell = RUBY_NOTHROW_NEW CharType[StrLen(src[i] + 1)];
				dstCell = StrCpy(dstCell, src[i]);
			}

			dst[newLen - 1] = nullptr;
			return dst;
		}

		static size_t StrArrLen(CharType** arr) {
		
		}

		static RUBY_FORCEINLINE CharType* StrCat(CharType* dst, CharType* src) {
			return std::strcat_s(dst, src);
		}

		static RUBY_FORCEINLINE CharType* StrCatN(CharType* dst, const CharType* src, size_t count) {
			return std::strncat_s(dst, src, count);
		}

		template<typename ReturnType = size_t>
		static RUBY_FORCEINLINE ReturnType StrLen(const CharType* str) {
			return static_cast<ReturnType>(std::strlen(str));
		}

		static RUBY_FORCEINLINE i32 StrCmp(const CharType* lhs, const CharType* rhs) {
			return std::strcmp(lhs, rhs);
		}

		static RUBY_FORCEINLINE bool StrCmpBool(const CharType* lhs, const CharType* rhs) {
			return (StrCmp(lhs, rhs) == 0);
		}


	};

	class CMemoryTools {
	public:
		using RawMemoryPtr = void*;

	public:
		static RUBY_FORCEINLINE RawMemoryPtr MemSet(RawMemoryPtr dst, i32 ch, size_t count) {
			return std::memset(dst, ch, count);
		}

		static RUBY_FORCEINLINE RawMemoryPtr MemCpy(RawMemoryPtr dst, const RawMemoryPtr src, size_t count) {
			return std::memcpy(dst, src, count);
		}

		static RUBY_FORCEINLINE i32 MemCmp(const RawMemoryPtr lhs, const RawMemoryPtr rhs, size_t count) {
			return std::memcmp(lhs, rhs, count);
		}

		static RUBY_FORCEINLINE bool MemCmpBool(const RawMemoryPtr lhs, const RawMemoryPtr rhs, size_t count) {
			return (MemCmp(lhs, rhs, count) == 0);
		}
	};

	using CString = BasicCString<char>;
	using CString16 = BasicCString<char16_t>;
	using CString32 = BasicCString<char32_t>;

	using CStringWide = BasicCString<wchar_t>;
}