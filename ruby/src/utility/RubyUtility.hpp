#pragma once

#include "Definitions.hpp"
#include <types/TypeTraits.hpp>
#include <types/Singleton.hpp>
#include "Enum.hpp"


namespace Ruby {
    RubyString extractTextFromFile(std::string_view path);

    template<typename Tx, typename... Args>
    Ptr<Tx> MakePtr(Args&&... args) {
        return std::make_shared<Tx>(std::forward<Args>(args)...);
    }

    template<typename Tx>
    Ptr<Tx> MakePtr(size_t size) {
        return std::make_shared<Tx>(size);
    }

    template<typename Tx, typename Ptr>
    Tx* isInstanceOf(Ptr* ptr) {
        return dynamic_cast<Tx*>(ptr);
    }
}