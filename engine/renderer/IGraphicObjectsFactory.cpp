#include "IGraphicObjectsFactory.hpp"

#include <backends/opengl/GraphicObjectsFactoryGL.hpp>



namespace Ruby {
    SharedPtr<IGraphicObjectsFactory> IGraphicObjectsFactory::Create() {
        return MakeShared<OpenGL::GraphicObjectsFactoryGL>();
    }
}
