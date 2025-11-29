#pragma once

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>


namespace Ruby {
    RUBY_ABSTRACT class ARenderInstance {
    public:
        RUBY_NODISCARD virtual bool Init() = 0;
        RUBY_NODISCARD virtual EGraphicAPI GetUsedAPI() const = 0;

        virtual void Shutdown() {}

        virtual ~ARenderInstance() = default;
    };
}