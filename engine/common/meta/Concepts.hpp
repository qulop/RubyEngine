#pragma once

#include "TypeTraits.hpp"


namespace Kiwi::Concepts {
    template<typename Tx, typename Ty>
    concept SameAs = std::same_as<Tx, Ty>;


    template<typename Tx>
    concept Range = requires(Tx& rng) {
        std::ranges::begin(rng);
        std::ranges::end(rng);
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

    template<typename T>
    concept TrivialCharacter = \
        SameAs<std::remove_cv_t<T>, char> ||
        SameAs<std::remove_cv_t<T>, wchar_t>;

    template<typename Fn, typename... Args>
    concept Callable = Traits::IsInvocable<Fn, Args...>::value;


    template<typename From, typename To>
    concept ConvertibleTo = std::convertible_to<From, To>;

    template<typename Der, typename Base>
    concept DerivedFrom = std::derived_from<Der, Base>;

    template<typename Der, typename Base>
    concept IsBaseOf = Traits::isBaseOf_v<Der, Base>;

    template<typename Tx>
    concept ImplementsEqualityOp = requires(Tx a, Tx b) {
        { a == b } -> ConvertibleTo<bool>;
    };

    template<typename Tx>
    concept ImplementsInequalityOp = requires(Tx a, Tx b) {
        { a != b } -> ConvertibleTo<bool>;
    };

    template<typename T>
    concept ContainsData = requires(T c) {
        T::value_type;

        { c.data() } -> ConvertibleTo<const typename T::value_type*>;
    };

    template<typename Tx>
    concept ContainerSTL = ContainsData<Tx> && requires(Tx c) {
        { c.size() } -> ConvertibleTo<size_t>;
        { c.empty() } -> ConvertibleTo<bool>;
    };
}