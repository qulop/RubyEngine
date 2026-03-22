#pragma once

#include <common/TypeTraits.hpp>


namespace Kiwi {
    struct Version {
    public:
        u32 versionFlags = 0;

    public:
        constexpr Version() = default;
        constexpr Version(u8 major, u8 minor, u8 patch) :
            versionFlags(((u32)major << 22) | ((u32)minor << 12) | ((u32)patch))
        {}

    public:
        KIWI_NODISCARD KIWI_FORCEINLINE constexpr u32 GetMajor() const {
            return versionFlags >> 22;
        }

        KIWI_NODISCARD KIWI_FORCEINLINE constexpr u32 GetMinor() const {
            return (versionFlags >> 12) & 0x3FF;
        }

        KIWI_NODISCARD KIWI_FORCEINLINE constexpr u32 GetPatch() const {
            return versionFlags & 0xFFF;
        }

        KIWI_NODISCARD constexpr u32 GetFlags() const {
            return versionFlags;
        }
    };
}