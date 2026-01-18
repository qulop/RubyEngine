#include "Renderer.hpp"

#include <renderer/pipeline/RenderInstance.hpp>
#include <renderer/pipeline/RenderPipeline.hpp>
#include <renderer/IGraphicObjectsFactory.hpp>
#include <renderer/GraphicDevice.hpp>


namespace Kiwi {
    bool Renderer::Init() {
        m_factory = IGraphicObjectsFactory::Create();

        m_instance = m_factory->CreateRenderInstance();
        if (!m_instance->Init()) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize the render instance({} for this session)",
                Cast<EGraphicAPI>::ToString(m_instance->GetUsedAPI()).value_or("")
            );
            return false;
        }

        m_graphicDevice = m_factory->CreateGraphicDevice();
        if (!m_graphicDevice->Init(m_instance)) {
            return false;
        }

        // m_renderPipeline = m_factory->CreateRenderPipeline(m_graphicDevice);
        // if (!m_renderPipeline->Init()) {
        //     KIWI_CTX_LOG(ERROR, "Failed to initialize a render pipeline");
        //     return false;
        // }

        m_shaderCompiler = m_factory->CreateShaderCompiler();

        return true;
    }

    void Renderer::SetViewport(const I32Rect& viewport) const {
        m_renderPipeline->SetViewport(viewport);
    }

    Renderer::~Renderer() {
        m_instance->Destroy();
    }
}
