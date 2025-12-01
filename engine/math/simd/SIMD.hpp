#pragma once


#include <types/TypeTraits.hpp>

#include <math/CommonFunc.hpp>
#include <math/vec/Vec4.hpp>

#include <intrin.h>
#include <xmmintrin.h>


namespace Kiwi {
    enum class ESimdSSE {
        SSE     = KIWI_BIT(0),
        SSE2    = KIWI_BIT(1),
        SSE3    = KIWI_BIT(2),
        SSE4_1  = KIWI_BIT(3),
        SSE4_2  = KIWI_BIT(4),
        SSE_FAMILY = SSE | SSE2 | SSE3 | SSE4_1 | SSE4_2
    };

    enum class ESimdAVX {
        AVX     = KIWI_BIT(0),
        AVX2    = KIWI_BIT(1),
        AVX_FAMILY = AVX | AVX2
    };




    template<Concepts::Number T>
    struct SplatByElement</*VecSize=*/4, T, VectorizationMode::SIMD> {
        template<u32 C>
            requires (C <= 3)
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            BasicVec4<T> r;
            _mm_storeu_ps(&r.x,
                _mm_shuffle_ps(
                    _mm_loadu_ps(&v.x),
                    _mm_loadu_ps(&v.x),
                    _MM_SHUFFLE(C, C, C, C)
                )
            );

            return r;
        }
    };
}
