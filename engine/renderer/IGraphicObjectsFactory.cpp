#include "IGraphicObjectsFactory.hpp"

#include <backends/opengl/GraphicObjectsFactoryGL.hpp>



namespace Kiwi {
    SharedPtr<IGraphicObjectsFactory> IGraphicObjectsFactory::Create() {
        return MakeShared<OpenGL::GraphicObjectsFactoryGL>();
    }
}
