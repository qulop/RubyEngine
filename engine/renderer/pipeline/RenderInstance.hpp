#pragma once

#include <utility/Definitions.hpp>

#include <core/Object.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>


namespace Kiwi {
    KIWI_ABSTRACT class ARenderInstance : public AObject {
        KIWI_CREATE_OBJECT(ARenderInstance)

    public:
    #ifdef KIWI_DEBUG_BUILD
        static constexpr bool ENABLE_DEBUG_CAPABILITIES = true;
    #else
        static constexpr bool ENABLE_DEBUG_CAPABILITIES = false;
    #endif

    public:
        using PFN_DebugCallback = std::function<void(StringView)>;

    public:
        KIWI_NODISCARD virtual bool Init() = 0;
        KIWI_NODISCARD virtual bool SetupDebugLayerCallback(const PFN_DebugCallback& debugCallback) = 0;

        KIWI_NODISCARD virtual EGraphicAPI GetUsedAPI() const = 0;

        virtual void Shutdown() {}

        ~ARenderInstance() override = default;
    };
}