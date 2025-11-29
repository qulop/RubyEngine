#include "GraphicDevice.hpp"

#include <backends/opengl/pipeline/ContextGL.hpp>
#include <backends/opengl/buffers/VertexBufferGL.hpp>


namespace Ruby {
    GraphicDevice::GraphicDevice(SharedPtr<IGraphicObjectsFactory> factoryPtr) :
        m_factory(factoryPtr)
    {}


    RUBY_NODISCARD EGraphicAPI GraphicDevice::GetCurrentSelectedAPI() {
        return EGraphicAPI::OpenGL;
    }

    SharedPtr<AVertexBuffer> GraphicDevice::AllocateVertexBuffer(EBufferType type) {
        switch (GetCurrentSelectedAPI()) {
            case EGraphicAPI::OpenGL:
                return MakeShared<OpenGL::VertexBufferGL>(type);
            default:
                return nullptr;
        }
    }

    void GraphicDevice::ReleaseObject(SharedPtr<IObjectGPU> buffer) {
        buffer->ReleaseObject();
    }
}
