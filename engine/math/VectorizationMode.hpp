#pragma once


namespace Ruby {
    enum class VectorizationMode {
        DEFAULT,
        SIMD,
    };

    consteval VectorizationMode getGlobalVectorizationMode() {
        return VectorizationMode::SIMD;
    }
}