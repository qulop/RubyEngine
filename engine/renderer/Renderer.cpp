#include "Renderer.hpp"

#include <renderer/IRenderContext.hpp>
#include <renderer/pipeline/RenderPipeline.hpp>
#include <renderer/IGraphicObjectsFactory.hpp>
#include <renderer/GraphicDevice.hpp>

#include <misc/WindowSubsystem.hpp>



namespace Kiwi {
    bool Renderer::Init() {
        m_factory = IGraphicObjectsFactory::Create();

        m_renderContext = IRenderContext::Create();
        if (!m_renderContext->Init()) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize a render context");
            return false;
        }

        auto windowSubsystem = GetSubsystem<WindowSubsystem>();
        KIWI_ENSURE(windowSubsystem);

        RenderPipelineInitInfo pipelineInitInfo;
        pipelineInitInfo.viewport = windowSubsystem->GetMainWindow()->GetFramebufferSizes();
        pipelineInitInfo.scissor = windowSubsystem->GetMainWindow()->GetFramebufferSizes();
        pipelineInitInfo.msaaSamplesCount = 4;

        if (!m_renderContext->GetPipeline()->Init(pipelineInitInfo)) {
            KIWI_CTX_LOG(ERROR, "Failed to initialize a pipeline");
            return false;
        }


        // m_graphicDevice = m_factory->CreateGraphicDevice();
        // if (!m_graphicDevice->Init()) {
        //     return false;
        // }

        // m_renderPipeline = m_factory->CreateRenderPipeline();
        // if (!m_renderPipeline->Init()) {
        //     KIWI_CTX_LOG(ERROR, "Failed to initialize a render pipeline");
        //     return false;
        // }

        // m_shaderCompiler = m_factory->CreateShaderCompiler();

        return true;
    }

    void Renderer::SetViewport(const I32Rect& viewport) const {
    }
}
