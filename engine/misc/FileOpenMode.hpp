#pragma once

#include <common/CString.hpp>
#include <common/cast/Cast.hpp>



namespace Kiwi {
    enum class EFileOpenMode {
        READ = (1 << 0),
        WRITE = (1 << 1),
        BINARY = (1 << 2),
        APPEND = (1 << 3),
        TRUNCATE = (1 << 4)
    };



    KIWI_FORCEINLINE EFileOpenMode operator|(EFileOpenMode lhs, EFileOpenMode rhs) {
        using T = std::underlying_type_t<EFileOpenMode>;

        return BasicCast::To<EFileOpenMode>(
            BasicCast::To<T>(lhs) | BasicCast::To<T>(rhs)
        );
    }

    KIWI_FORCEINLINE EFileOpenMode& operator|=(EFileOpenMode& lhs, EFileOpenMode rhs) {
        lhs = lhs | rhs;
        return lhs;
    }


    KIWI_FORCEINLINE EFileOpenMode operator&(EFileOpenMode lhs, EFileOpenMode rhs) {
        using T = std::underlying_type_t<EFileOpenMode>;

        return BasicCast::To<EFileOpenMode>(
            BasicCast::To<T>(lhs) & BasicCast::To<T>(rhs)
        );
    }

    KIWI_FORCEINLINE EFileOpenMode& operator&=(EFileOpenMode& lhs, EFileOpenMode rhs) {
        lhs = lhs & rhs;
        return lhs;
    }

    
    template<>
    struct CastTraits<EFileOpenMode> {
        KIWI_NODISCARD KIWI_FORCEINLINE static Opt<String> ToCStyleOpenMode(EFileOpenMode mode) {
            String res;

            auto hasWrite = (mode & EFileOpenMode::WRITE) == EFileOpenMode::WRITE;
            auto hasRead = (mode & EFileOpenMode::READ) == EFileOpenMode::READ;
            auto hasBinary = (mode & EFileOpenMode::BINARY) == EFileOpenMode::BINARY;
            auto hasAppend = (mode & EFileOpenMode::APPEND) == EFileOpenMode::APPEND;
            auto hasTrunc = (mode & EFileOpenMode::TRUNCATE) == EFileOpenMode::TRUNCATE;

            if ((hasWrite && !hasRead) || (hasRead && !hasWrite)) {
                if ((hasRead && !hasWrite)) {
                    res += 'r';
                }
                else {
                    if (hasAppend) {
                        res += 'a';
                    }
                    else {
                        res += 'w';
                    }
                }

            }
            else if (hasWrite && hasRead) {
                if (hasAppend) {
                    res += "a+";
                }
                else if (hasTrunc) {
                    res += "w+";
                }
                else {
                    res += "r+";
                }
            }
            else {
                return nullopt;
            }


            if (hasBinary) {
                res += 'b';
            }

            return res;
        }
    };
}