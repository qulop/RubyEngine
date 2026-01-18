#include "RenderPipeline.hpp"


namespace Kiwi {
    ARenderPipeline::ARenderPipeline(const SharedPtr<GraphicDevice>& device) :
            m_graphicDevice(device)
    {}


    bool ARenderPipeline::Init() {
        KIWI_ASSERT(m_graphicDevice, "GraphicDevice didn't set");

        KIWI_CTX_LOG(INFO, "Starting the initialization process...");
        KIWI_LOG(INFO, "Selected renderer: {}. Renderer device vendor: {}",
            GetRendererDeviceName(),
            GetRendererDeviceVendor()
        );


        KIWI_LOG(INFO, "Render pipeline first initialization step done");
    }

    void ARenderPipeline::SetViewport(const I32Rect& viewport) {
        m_viewport = viewport;
    }

    bool ARenderPipeline::InitBuffers() {

    }
}
