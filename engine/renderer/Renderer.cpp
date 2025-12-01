#include "Renderer.hpp"

#include <types/Logger.hpp>

#include <renderer/pipeline/RenderInstance.hpp>
#include <renderer/pipeline/RenderPipeline.hpp>
#include <renderer/IGraphicObjectsFactory.hpp>
#include <renderer/GraphicDevice.hpp>


namespace Kiwi {
    bool Renderer::Init() {
        m_factory = IGraphicObjectsFactory::Create();

        m_instance = m_factory->CreateRenderInstance();
        if (!m_instance->Init()) {
            KIWI_ERROR("Renderer::Init() : Failed to initialize the render instance({} for this session)",
                Cast<EGraphicAPI>::ToString(m_instance->GetUsedAPI()).value_or("")
            );
            return false;
        }

        m_graphicDevice = MakeShared<GraphicDevice>(m_factory);

        m_renderPipeline = m_factory->CreateRenderPipeline(m_graphicDevice);
        if (!m_renderPipeline->Init()) {
            KIWI_ERROR("Renderer::Init() : Failed to initialize a render pipeline");
            return false;
        }

        m_shaderCompiler = m_factory->CreateShaderCompiler();

        return true;
    }

    void Renderer::SetViewport(const IRect& viewport) const {
        m_renderPipeline->SetViewport(viewport);
    }
}
