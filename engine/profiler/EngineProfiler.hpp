#pragma once

#include <utility/Definitions.hpp>
#include <types/Logger.hpp>

#include <tracy/Tracy.hpp>



namespace Ruby {
    class EngineProfiler {
    public:
        RUBY_NODISCARD static constexpr bool IsEnabled() {
        #if defined(RUBY_ENABLE_PROFILING) && defined(TRACY_ENABLE)
            return true;
        #else
            return false;
        #endif
        }


        RUBY_NODISCARD static bool IsConnectedToServer();
    };
}


#ifdef TRACY_ENABLE
    #define RUBY_PROFILE_ZONE                   ZoneScoped
    #define RUBY_PROFILE_ZONE_COLOR(color)      ZoneScopedC(color)
    #define RUBY_PROFILE_ZONE_NAME(name)        ZoneScopedN(name)
    #define RUBY_PROFILE_ZONE_NC(name, color)   ZoneScopedNC(name, color)

    #define RUBY_ZONE_SET_TEXT(txt, sz)         ZoneText(txt, sz)
    #define RUBY_ZONE_SET_TEXT_F(fmt, ...)      ZoneTextF(txt, __VA_ARGS__)
    #define RUBY_ZONE_SET_COLOR(color)          ZoneText(color)
    #define RUBY_ZONE_SET_VALUE(val)            ZoneValue(val)
    #define RUBY_ZONE_IS_ACTIVE()               ZoneIsActive
#else
    #define RUBY_PROFILE_ZONE                   RUBY_EMPTY_MACRO
    #define RUBY_PROFILE_ZONE_COLOR(color)      RUBY_EMPTY_MACRO
    #define RUBY_PROFILE_ZONE_NAME(name)        RUBY_EMPTY_MACRO
    #define RUBY_PROFILE_ZONE_NC(name, color)   RUBY_EMPTY_MACRO

    #define RUBY_ZONE_SET_TEXT(txt, sz)         RUBY_EMPTY_MACRO
    #define RUBY_ZONE_SET_TEXT_F(fmt, ...)      RUBY_EMPTY_MACRO
    #define RUBY_ZONE_SET_COLOR(color)          RUBY_EMPTY_MACRO
    #define RUBY_ZONE_SET_VALUE(val)            RUBY_EMPTY_MACRO
    #define RUBY_ZONE_IS_ACTIVE()               RUBY_EMPTY_MACRO
#endif