#include "Renderer.hpp"

#include <renderer/IRenderContext.hpp>
#include <renderer/pipeline/RenderPipeline.hpp>
#include <renderer/IGraphicObjectsFactory.hpp>
#include <renderer/GraphicDevice.hpp>



namespace Kiwi {
    bool Renderer::Init() {
        m_factory = IGraphicObjectsFactory::Create();

        m_renderContext = IRenderContext::Create();
        if (!m_renderContext->Init()) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize a render context for {}",
                Cast<EGraphicAPI>::ToString(m_renderContext->GetUsedAPI()).value_or("")
            );
            return false;
        }

        m_graphicDevice = m_factory->CreateGraphicDevice();
        if (!m_graphicDevice->Init()) {
            return false;
        }

        m_renderPipeline = m_factory->CreateRenderPipeline();
        if (!m_renderPipeline->Init()) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize a render pipeline");
            return false;
        }

        m_shaderCompiler = m_factory->CreateShaderCompiler();

        return true;
    }

    void Renderer::SetViewport(const I32Rect& viewport) const {
        m_renderPipeline->SetViewport(viewport);
    }
}
