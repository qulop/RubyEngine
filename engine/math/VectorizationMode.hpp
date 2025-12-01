#pragma once


namespace Kiwi {
    enum class VectorizationMode {
        DEFAULT,
        SIMD,
    };

    consteval VectorizationMode GetGlobalVectorizationMode() {
        return VectorizationMode::SIMD;
    }
}