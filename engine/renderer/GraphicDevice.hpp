#pragma once

#include <core/Object.hpp>

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>
#include <renderer/buffers/ObjectGPU.hpp>


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_ABSTRACT class ARenderInstance;

        KIWI_INTERFACE IGraphicObjectsFactory;

        KIWI_ABSTRACT class AVertexBuffer;
    )


    struct PhysicalGraphicDeviceFeatures {
        String vendorName;
        String deviceName;

    };


    KIWI_ABSTRACT class AGraphicDevice : public AObject {
        KIWI_CREATE_OBJECT(AGraphicDevice)

    public:
        KIWI_NODISCARD virtual bool Init(SharedPtr<ARenderInstance> renderInstance) {
            return true;
        }

    private:
        SharedPtr<IGraphicObjectsFactory> m_factory;
    };
}
