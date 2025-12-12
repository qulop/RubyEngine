#pragma once

#include <utility/Definitions.hpp>

#include <types/cast/Cast.hpp>


namespace Kiwi {
    enum class EErrorIO {
        UNKNOWN = KIWI_BIT(0),
        DOES_NOT_EXIST = KIWI_BIT(1),
        PERMISSION_DENIED = KIWI_BIT(2),
        INVALID_ARGUMENT = KIWI_BIT(3),
        TOO_MANY_OPEN_FILES = KIWI_BIT(4),
        IS_DIRECTORY = KIWI_BIT(5),
        NO_SPACE_LEFT = KIWI_BIT(6),
        UNEXPECTED_EOF = KIWI_BIT(7),
    };


    template<>
    struct CastTraits<EErrorIO> {
        KIWI_NODISCARD KIWI_FORCEINLINE static String ToString(EErrorIO v) {
            switch (v) {
                case EErrorIO::DOES_NOT_EXIST:
                    return String("DOES_NOT_EXIST");
                case EErrorIO::PERMISSION_DENIED:
                    return String("PERMISSION_DENIED");
                case EErrorIO::INVALID_ARGUMENT:
                    return String("INVALID_MODE");
                case EErrorIO::TOO_MANY_OPEN_FILES:
                    return String("TOO_MANY_OPEN_FILES");
                case EErrorIO::IS_DIRECTORY:
                    return String("IS_DIRECTORY");
                case EErrorIO::NO_SPACE_LEFT:
                    return String("NO_SPACE_LEFT");
                default:
                    return String("UNKNOWN");
            }
        }

        KIWI_NODISCARD KIWI_FORCEINLINE static EErrorIO FromPosixCodes(errno_t v) {
            switch (v) {
            case ENOENT:
                return EErrorIO::DOES_NOT_EXIST;
            case EACCES:
                return EErrorIO::PERMISSION_DENIED;
            case EINVAL:
                return EErrorIO::INVALID_ARGUMENT;
            case EMFILE:
                return EErrorIO::TOO_MANY_OPEN_FILES;
            case EISDIR:
                return EErrorIO::IS_DIRECTORY;
            case ENOSPC:
                return EErrorIO::NO_SPACE_LEFT;
            default:
                return EErrorIO::UNKNOWN;
            }
        }
    };


    template<typename TErrorEnum>
        requires requires(TErrorEnum t) {
            { Cast<TErrorEnum>::ToString(t) } -> std::convertible_to<String>;
        }
    struct Error {
        using ErrorEnumType = TErrorEnum;

        TErrorEnum kind;
        String desc;

    public:
        KIWI_NODISCARD static Error FromKind(ErrorEnumType v) {
            return {
                .kind = v,
                .desc = Cast<ErrorEnumType>::ToString(v)
            };
        }
    };

    KIWI_FORCEINLINE Error<EErrorIO> MakeErrorIOFromPosixCode(errno_t v) {
        return Error<EErrorIO>::FromKind(
            Cast<EErrorIO>::FromPosixCodes(v)
        );
    }
}