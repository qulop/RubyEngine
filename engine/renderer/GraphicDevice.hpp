#pragma once

#include <core/Object.hpp>

#include <utility/Definitions.hpp>

#include <renderer/pipeline/GraphicAPI.hpp>


namespace Kiwi {
    class ARenderInstance;
    KIWI_INTERFACE IGraphicObjectsFactory;



    struct PhysicalGraphicDeviceFeatures {
        String vendorName;
        String deviceName;

    };


    KIWI_ABSTRACT class AGraphicDevice : public AObject {
        KIWI_CREATE_OBJECT(AGraphicDevice)

    public:
        KIWI_NODISCARD virtual bool Init() {
            KIWI_CTX_LOG(INFO, "Started to initialize a graphic device...");

            return true;
        }
    };
}
