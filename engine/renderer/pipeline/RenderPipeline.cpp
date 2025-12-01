#include "RenderPipeline.hpp"

#include <types/Logger.hpp>


namespace Kiwi {
    ARenderPipeline::ARenderPipeline(const SharedPtr<GraphicDevice>& device) :
            m_graphicDevice(device)
    {}


    bool ARenderPipeline::Init() {
        KIWI_ASSERT(m_graphicDevice, "GraphicDevice didn't set");

        KIWI_INFO("ARenderPipeline::Init() : Starting the initialization process...");
        KIWI_INFO("Selected renderer: {}. Renderer device vendor: {}",
            GetRendererDeviceName(),
            GetRendererDeviceVendor()
        );


        KIWI_INFO("ARenderPipeline::Init() : First initialization step done");
    }

    void ARenderPipeline::SetViewport(const IRect& viewport) {
        m_viewport = viewport;
    }

    bool ARenderPipeline::InitBuffers() {

    }
}
