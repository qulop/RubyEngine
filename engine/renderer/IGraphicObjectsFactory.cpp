#include "IGraphicObjectsFactory.hpp"

#include <backends/opengl/GraphicObjectsFactoryGL.hpp>
#include <backends/vulkan/GraphicObjectsFactoryVK.hpp>



namespace Kiwi {
    SharedPtr<IGraphicObjectsFactory> IGraphicObjectsFactory::Create() {
        return MakeShared<Vulkan::GraphicObjectsFactoryVK>();
    }
}
