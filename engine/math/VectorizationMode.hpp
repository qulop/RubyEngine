#pragma once


namespace Ruby {
    enum class VectorizationMode {
        DEFAULT,
        SIMD,
    };

    consteval VectorizationMode GetGlobalVectorizationMode() {
        return VectorizationMode::SIMD;
    }
}