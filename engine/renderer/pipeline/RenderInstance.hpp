#pragma once

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>


namespace Kiwi {
    KIWI_ABSTRACT class ARenderInstance {
    public:
        KIWI_NODISCARD virtual bool Init() = 0;
        KIWI_NODISCARD virtual EGraphicAPI GetUsedAPI() const = 0;

        virtual void Shutdown() {}

        virtual ~ARenderInstance() = default;
    };
}