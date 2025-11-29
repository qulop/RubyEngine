#pragma once

#include <utility/Definitions.hpp>

#include <types/TypeTraits.hpp>
#include <types/cast/Cast.hpp>
#include <memory/Memory.hpp>


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

        static CharType** StrArrCpy(const CharType** src, size_t len, size_t offset = 0) {
            if (!src || offset > len) {
                return nullptr;
            }

            size_t numToCopy = len - offset;
            auto** dstArr = RUBY_NOTHROW_NEW CharType*[numToCopy + 1];
            if (!dstArr) {
                return nullptr;
            }

            for (auto i = 0; i < numToCopy; i++) {
                size_t srcIndex = i + offset;
                size_t srcLen = StrLen(src[srcIndex]);

                dstArr[i] = RUBY_NOTHROW_NEW CharType[srcLen + 1];
                if (!dstArr[i]) {
                    for (auto j = 0; j < i; j++) {
                        delete[] dstArr[j];
                    }

                    delete[] dstArr;
                    return nullptr;
                }

                StrCpy(dstArr[i], srcLen + 1, src[srcIndex]);
            }

            dstArr[numToCopy] = nullptr;
            return dstArr;
        }

        RUBY_FORCEINLINE static CharType* StrCat(CharType* dst, size_t dstsz, CharType* src) {
            return (strcat_s(dst, dstsz, src) == 0) ? dst : nullptr;
        }

        RUBY_FORCEINLINE static CharType* StrCatN(CharType* dst, size_t dstsz, const CharType* src, size_t count) {
            return (strncat_s(dst, dstsz, src, count)) ? dst : nullptr;
        }

        template<typename TReturnType = size_t>
        RUBY_FORCEINLINE static TReturnType StrLen(const CharType* str) {
            return BasicCast::To<TReturnType>(std::strlen(str));
        }

        RUBY_FORCEINLINE static i32 StrCmp(const CharType* lhs, const CharType* rhs) {
            return std::strcmp(lhs, rhs);
        }

        RUBY_FORCEINLINE static bool StrCmpBool(const CharType* lhs, const CharType* rhs) {
            return (StrCmp(lhs, rhs) == 0);
        }

        RUBY_NODISCARD RUBY_FORCEINLINE static CharType* New(size_t sz) {
            return (CharType*)Memory::Malloc(sz);
        }

        RUBY_FORCEINLINE static void Delete(CharType* ptr) {
            Memory::Free(ptr);
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

        RUBY_FORCEINLINE static void MemSetSafe(RawMemoryPtr mem, size_t count) {
            // TODO: Not as safe, as it could be
            volatile byte* ptr = BasicCast::To<byte*>(mem);
            for (size_t i = 0; i < count; i++) {
                ptr[i] = 0;
            }
        }
    };

	using CString = BasicCString<char>;
}