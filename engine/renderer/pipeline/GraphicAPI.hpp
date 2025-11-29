#pragma once

#include <types/cast/CastTraits.hpp>


namespace Ruby {
    enum class EGraphicAPI {
        AUTO,
        OpenGL,
        Vulkan,
        DirectX11,
        DirectX12
    };


    template<>
    struct CastTraits<EGraphicAPI> {
        RUBY_NODISCARD RUBY_FORCEINLINE static Opt<String> ToString(EGraphicAPI val) {
            switch (val) {
                case EGraphicAPI::OpenGL:
                    return "OpenGL";
                case EGraphicAPI::Vulkan:
                    return "Vulkan";
                case EGraphicAPI::DirectX11:
                    return "DirectX11";
                case EGraphicAPI::DirectX12:
                    return "DirectX12";
                case EGraphicAPI::AUTO:
                    return "AUTO";
                default:
                    return nullopt;
            }
        }
    };

}