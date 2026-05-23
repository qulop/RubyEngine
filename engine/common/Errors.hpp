#pragma once

#include <common/types/String.hpp>


namespace Kiwi {
    enum class EGeneralError {
        NOT_FOUND,
        OUT_OF_MEMORY,
        IS_NOT_COMPLETE,
        BUFF_OVERFLOW,
        INITIALIZE_FAILED,
        INVALID_ARGUMENT,
        OUT_OF_RANGE,
        BAD_FORMAT,
        COMPILE_ERROR,
        CREATE_FAIL
    };

    enum class EErrorIO {
        UNKNOWN,
        DOES_NOT_EXIST,
        PERMISSION_DENIED,
        INVALID_ARGUMENT,
        TOO_MANY_OPEN_FILES,
        IS_DIRECTORY,
        NO_SPACE_LEFT,
        UNEXPECTED_EOF,
    };


    template<>
    struct CastTraits<EGeneralError> {
        KIWI_NODISCARD KIWI_FORCEINLINE static String ToString(EGeneralError v) {
            switch (v) {
                case EGeneralError::NOT_FOUND:
                    return "NOT_FOUND";
                case EGeneralError::OUT_OF_MEMORY:
                    return "OUT_OF_MEMORY";
                case EGeneralError::IS_NOT_COMPLETE:
                    return "IS_NOT_COMPLETE";
                case EGeneralError::BUFF_OVERFLOW:
                    return "OVERFLOW";
                case EGeneralError::INITIALIZE_FAILED:
                    return "INITIALIZE_FAILED";
                default:
                    std::unreachable();
            }
        }
    };

    template<>
    struct CastTraits<EErrorIO> {
        KIWI_NODISCARD KIWI_FORCEINLINE static String ToString(EErrorIO v) {
            switch (v) {
                case EErrorIO::DOES_NOT_EXIST:
                    return "DOES_NOT_EXIST";
                case EErrorIO::PERMISSION_DENIED:
                    return "PERMISSION_DENIED";
                case EErrorIO::INVALID_ARGUMENT:
                    return "INVALID_ARGUMENT";
                case EErrorIO::TOO_MANY_OPEN_FILES:
                    return "TOO_MANY_OPEN_FILES";
                case EErrorIO::IS_DIRECTORY:
                    return "IS_DIRECTORY";
                case EErrorIO::NO_SPACE_LEFT:
                    return "NO_SPACE_LEFT";
                default:
                    return "UNKNOWN";
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


    template<Concepts::Enumeration EErrorEnum>
    struct Error {
        using ErrorEnumeration = EErrorEnum;

        EErrorEnum kind;
        Opt<String> desc;
    
    public:
        KIWI_NODISCARD static Error FromKind(ErrorEnumeration v)
            requires requires(ErrorEnumeration e) { { Cast<ErrorEnumeration>::ToString(e) } -> std::convertible_to<String>; }
        {
            return {
                .kind = v,
                .desc = Cast<ErrorEnumeration>::ToString(v)
            };
        }

    public:
        KIWI_NODISCARD Opt<String> GetDescription() const {
            if (desc) {
                return *desc;
            }

            if constexpr (Concepts::CanBeCastedToString<EErrorEnum>) {
                return Cast<ErrorEnumeration>::ToString();
            }
            else {
                return nullopt;
            }
        }

        KIWI_NODISCARD bool operator==(const Error& other) const noexcept {
            return kind == other.kind && desc == other.desc;
        }
    };



    template<typename TErrorEnum>
    using StatusResult = Status<Error<TErrorEnum>>;
}