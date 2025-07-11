#pragma once

#include "TypeTraits.hpp"


namespace Ruby::Concepts {
    template<typename Tx>
    concept Iterable = requires(std::ranges::range_value_t<Tx> rng) {
        rng.begin(); rng.end();
        rng.Begin(); rng.End();
    };

    template<typename Tx>
    concept Integral = (std::is_integral_v<Tx>);

    template<typename Tx>
    concept FloatingPoint = (std::is_floating_point_v<Tx>);

    template<typename Tx>
    concept Number = (std::is_integral_v<Tx> || std::is_floating_point_v<Tx>);


    template<typename Tx>
    concept Enum = (std::is_enum_v<Tx>);

    template<typename Tx>
    concept CString = \
        std::same_as<std::remove_cv_t<Tx>, char*> ||
        std::same_as<std::remove_cv_t<Tx>, wchar_t*>;

    template<typename Fn, typename... Args>
    concept Callable = Traits::IsInvocable<Fn, Args...>::value;


    template<typename Tx>
    concept ImplementsEqualityOp = requires(Tx a, Tx b) {
        { a == b } -> std::convertible_to<bool>;
    };

    template<typename Tx>
    concept ImplementsInequalityOp = requires(Tx a, Tx b) {
        { a != b } -> std::convertible_to<bool>;
    };

    template<typename Tx>
    concept ContainerSTL = requires(Tx cont) {
        { cont.size() } -> std::same_as<size_t>;
        { cont.empty() } -> std::convertible_to<bool>;
    };
}