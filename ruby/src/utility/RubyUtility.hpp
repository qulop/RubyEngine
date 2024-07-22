#pragma once

#include "Definitions.hpp"
#include "Logger.hpp"
#include "TypeTraits.hpp"
#include "Singleton.hpp"
#include "Enum.hpp"


namespace Ruby {
    template<typename Tx, typename... Args>
    Ptr<Tx> MakePtr(Args&&... args) {
        return std::make_shared<Tx>(std::forward<Args>(args)...);
    }

    template<typename Tx>
    Ptr<Tx> MakePtr(size_t size) {
        return std::make_shared<Tx>(size);
    }

    template<typename Ret, typename... Args>
    struct NumberOfArguments {
        static constexpr size_t Value = sizeof...(Args);
    };

    template<typename Ret, typename... Args>
    constexpr size_t g_NumberOfArguments_v = NumberOfArguments<Ret, Args...>::Value;

    RubyString extractTextFromFile(std::string_view path);
}