#pragma once

#include <core/Object.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>



namespace Kiwi {
    KIWI_INTERFACE IRenderContext : public AObject {
        KIWI_CREATE_OBJECT(IRenderContext)

    public:
        using PFN_DebugCallback = std::function<void(StringView)>;

    public:
        KIWI_NODISCARD static SharedPtr<IRenderContext> Create();

    public:
        KIWI_NODISCARD virtual bool Init() = 0;
        KIWI_NODISCARD virtual bool SetupDebugLayerCallback(const PFN_DebugCallback& debugCallback) = 0;

        KIWI_NODISCARD virtual EGraphicAPI GetUsedAPI() const = 0;

        virtual void Destroy() = 0;

        ~IRenderContext() override = default;
    };
}