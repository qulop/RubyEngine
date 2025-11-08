#pragma once

#include <types/TypeTraits.hpp>
#include <types/Concepts.hpp>

#include <math/vec/Vec4.hpp>
#include <math/VectorizationMode.hpp>


namespace Ruby {
    template<size_t VecSize, Concepts::Number T, VectorizationMode V>
    struct SplatByElement {
        static_assert(Traits::AlwaysFalse::value, "Base specialization is not allowed");
    };



    template<Concepts::Number T>
    struct SplatByElement<4, T, VectorizationMode::DEFAULT> {
        template<u32 C>
            requires (C <= 3)
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            BasicVec4 res{ BasicCast::To<T>(0) };

            for (size_t i = 0; i < BasicVec4<T>::Size(); i++) {
                res[i] = v[C];
            }

            return v;
        }
    };


    template<size_t VecSize, Concepts::Number T, VectorizationMode V>
    struct SplatX {
        static_assert(Traits::AlwaysFalse::value, "Base specialization is not allowed");
    };

    template<Concepts::Number T, VectorizationMode V>
    struct SplatX<4, T, V> {
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            return SplatByElement<4, T, V>::template Call<0>(v);
        }
    };

    
    template<size_t VecSize, Concepts::Number T, VectorizationMode V>
    struct SplatY {
        static_assert(Traits::AlwaysFalse::value, "Base specialization is not allowed");
    };

    template<Concepts::Number T, VectorizationMode V>
    struct SplatY<4, T, V> {
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            return SplatByElement<4, T, V>::template Call<1>(v);
        }
    };


    template<size_t VecSize, Concepts::Number T, VectorizationMode V>
    struct SplatZ {
        static_assert(Traits::AlwaysFalse::value, "Base specialization is not allowed");
    };

    template<Concepts::Number T, VectorizationMode V>
    struct SplatZ<4, T, V> {
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            return SplatByElement<4, T, V>::template Call<2>(v);
        }
    };


    template<size_t VecSize, Concepts::Number T, VectorizationMode V>
    struct SplatW {
        static_assert(Traits::AlwaysFalse::value, "Base specialization is not allowed");
    };

    template<Concepts::Number T, VectorizationMode V>
    struct SplatW<4, T, V> {
        constexpr static BasicVec4<T> Call(const BasicVec4<T>& v) {
            return SplatByElement<4, T, V>::template Call<3>(v);
        }
    };
}
