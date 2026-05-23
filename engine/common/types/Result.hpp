#pragma once

#include <common/PCH.hpp>
#include <common/Errors.hpp>
#include <common/meta/Concepts.hpp>
#include <common/Debug.hpp>


namespace Kiwi {
    template<typename T>
     struct Success {
        T successValue;


        template<typename... Args>
        explicit constexpr Success(std::in_place_t, Args&&... args) :
            successValue(std::forward<Args>(args)...)
        {}

        explicit constexpr Success(const T& r) :
            successValue(r)
        {}

        explicit constexpr Success(T&& r) noexcept :
            successValue(std::move(r))
        {}

        constexpr Success& operator=(const Success& other) = default;
        constexpr Success& operator=(Success&&) noexcept = default;
    };

    template<>
    struct Success<void> {
        constexpr Success() noexcept = default;
    };



    template<typename TSuccess, Concepts::Enumeration TErrEnum = EGeneralError>
    class Result final {
    public:
        using SuccessType = TSuccess;
        using ErrorEnumeration = TErrEnum;

    public:
        constexpr Result() = default;
        constexpr Result(const Result&) = default;
        constexpr Result(Result&&) noexcept = default;

        template<typename S>
            requires std::same_as<std::remove_cvref_t<S>, Success<SuccessType>>
        constexpr Result(S&& success) :
            m_result(std::forward<S>(success).successValue)
        {}

        template<typename E>
            requires std::same_as<std::remove_cvref_t<E>, Error<ErrorEnumeration>>
        constexpr Result(E&& err) :
            m_result(std::unexpected(std::forward<E>(err)))
        {}

        KIWI_NODISCARD constexpr bool HasValue() const {
            return m_result.has_value();
        }

        KIWI_NODISCARD constexpr bool HasError() const {
            return !HasValue();
        }

        KIWI_NODISCARD constexpr SuccessType& GetValue() & {
            KIWI_ENSURE(HasValue());

            return m_result.value();
        }

        KIWI_NODISCARD constexpr const SuccessType& GetValue() const& {
            KIWI_ENSURE(HasValue());

            return m_result.value();
        }

        KIWI_NODISCARD constexpr SuccessType StealValue() {
            KIWI_ENSURE(HasValue());

            return std::move(m_result).value();
        }

        KIWI_NODISCARD constexpr Error<ErrorEnumeration> GetError() const& {
            KIWI_ENSURE(HasError());

            return m_result.error();
        }

        KIWI_NODISCARD constexpr Error<ErrorEnumeration> StealError() {
            KIWI_ENSURE(HasError());

            return std::move(m_result).error();
        }

        template<Concepts::ConvertibleTo<SuccessType> TDefault = std::remove_cv_t<SuccessType>>
        KIWI_NODISCARD constexpr SuccessType ValueOr(TDefault&& defaultValue) const {
            return m_result.value_or(std::forward<TDefault>(defaultValue));
        }

        KIWI_NODISCARD constexpr decltype(auto) operator*() const {
            return m_result.operator*();
        }

        KIWI_NODISCARD constexpr decltype(auto) operator*() {
            return m_result.operator*();
        }

        constexpr decltype(auto) operator->() const {
            return m_result.operator->();
        }

        constexpr decltype(auto) operator->() {
            return m_result.operator->();
        }

        constexpr explicit operator bool() const noexcept {
            return HasValue();
        }

        ~Result() = default;

    private:
        std::expected<SuccessType, Error<ErrorEnumeration>> m_result;
    };


    // Partial specialization where is no success value(for `void` cases)
    template<Concepts::Enumeration TErrEnum>
    class Result<void, TErrEnum> final {
    public:
        using SuccessType = void;
        using ErrorEnumeration = TErrEnum;

    public:
        constexpr Result() = default;
        constexpr Result(const Result&) = default;
        constexpr Result(Result&&) noexcept = default;

        constexpr Result(Success<void>) :
            m_result()
        {}

        template<typename E>
            requires std::same_as<std::remove_cvref_t<E>, Error<ErrorEnumeration>>
        constexpr Result(E&& err) :
            m_result(std::unexpected(std::forward<E>(err)))
        {}

        KIWI_NODISCARD constexpr bool HasValue() const {
            return m_result.has_value();
        }

        KIWI_NODISCARD constexpr bool HasError() const {
            return !HasValue();
        }

        KIWI_NODISCARD constexpr Error<ErrorEnumeration> GetError() const& {
            KIWI_ENSURE(HasError());

            return m_result.error();
        }

        KIWI_NODISCARD constexpr Error<ErrorEnumeration> StealError() {
            KIWI_ENSURE(HasError());

            return std::move(m_result).error();
        }

        constexpr explicit operator bool() const noexcept {
            return HasValue();
        }

        ~Result() = default;

    private:
        std::expected<void, Error<ErrorEnumeration>> m_result;
    };
}
