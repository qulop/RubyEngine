#include "RenderPipeline.hpp"

#include <types/Logger.hpp>


namespace Ruby {
    ARenderPipeline::ARenderPipeline(const SharedPtr<GraphicDevice>& device) :
            m_graphicDevice(device)
    {}


    bool ARenderPipeline::Init() {
        RUBY_ASSERT(m_graphicDevice, "GraphicDevice didn't set");

        RUBY_INFO("ARenderPipeline::Init() : Starting the initialization process...");
        RUBY_INFO("Selected renderer: {}. Renderer device vendor: {}",
            GetRendererDeviceName(),
            GetRendererDeviceVendor()
        );


        RUBY_INFO("ARenderPipeline::Init() : First initialization step done");
    }

    void ARenderPipeline::SetViewport(const IRect& viewport) {
        m_viewport = viewport;
    }

    bool ARenderPipeline::InitBuffers() {

    }
}
