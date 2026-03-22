#pragma once

#include <common/Definitions.hpp>

#include <tracy/Tracy.hpp>



namespace Kiwi {
    class EngineProfiler {
    public:
        KIWI_NODISCARD static constexpr bool IsEnabled() {
        #if defined(KIWI_ENABLE_PROFILING) && defined(TRACY_ENABLE)
            return true;
        #else
            return false;
        #endif
        }


        KIWI_NODISCARD static bool IsConnectedToServer();
    };
}


#ifdef TRACY_ENABLE
    #define KIWI_PROFILE_ZONE                   ZoneScoped
    #define KIWI_PROFILE_ZONE_COLOR(color)      ZoneScopedC(color)
    #define KIWI_PROFILE_ZONE_NAME(name)        ZoneScopedN(name)
    #define KIWI_PROFILE_ZONE_NC(name, color)   ZoneScopedNC(name, color)

    #define KIWI_ZONE_SET_TEXT(txt, sz)         ZoneText(txt, sz)
    #define KIWI_ZONE_SET_TEXT_F(fmt, ...)      ZoneTextF(txt, __VA_ARGS__)
    #define KIWI_ZONE_SET_COLOR(color)          ZoneText(color)
    #define KIWI_ZONE_SET_VALUE(val)            ZoneValue(val)
    #define KIWI_ZONE_IS_ACTIVE()               ZoneIsActive
#else
    #define KIWI_PROFILE_ZONE                   KIWI_EMPTY_MACRO
    #define KIWI_PROFILE_ZONE_COLOR(color)      KIWI_EMPTY_MACRO
    #define KIWI_PROFILE_ZONE_NAME(name)        KIWI_EMPTY_MACRO
    #define KIWI_PROFILE_ZONE_NC(name, color)   KIWI_EMPTY_MACRO

    #define KIWI_ZONE_SET_TEXT(txt, sz)         KIWI_EMPTY_MACRO
    #define KIWI_ZONE_SET_TEXT_F(fmt, ...)      KIWI_EMPTY_MACRO
    #define KIWI_ZONE_SET_COLOR(color)          KIWI_EMPTY_MACRO
    #define KIWI_ZONE_SET_VALUE(val)            KIWI_EMPTY_MACRO
    #define KIWI_ZONE_IS_ACTIVE()               KIWI_EMPTY_MACRO
#endif