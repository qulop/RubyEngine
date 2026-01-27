#include "IRenderContext.hpp"

#include <backends/vulkan/RenderContextVK.hpp>


namespace Kiwi {
    SharedPtr<IRenderContext> IRenderContext::Create() {
        return MakeShared<Vulkan::RenderContextVK>();
    }
}
