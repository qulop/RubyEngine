#include "VulkanCore.hpp"



namespace {
    const Kiwi::Vector<Kiwi::String> REQUIRED_VALIDATION_LAYERS = {
        "VK_LAYER_KHRONOS_validation"
    };
}


namespace Kiwi::Vulkan {
    Vector<String> VulkanCore::GetRequiredValidationLayers() const {
        return REQUIRED_VALIDATION_LAYERS;
    }
}
