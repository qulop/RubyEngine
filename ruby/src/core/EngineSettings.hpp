#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>

namespace Ruby
{

    struct RUBY_API EngineSettingsStruct
    {
    private:
        uint16_t m_maxFPS = 120;
        float m_timestep = 1000.0f / m_maxFPS;
        uint8_t m_interval = 1; // time step after how long fps will be caclucalted

    public:
    // getters
        uint16_t GetMaxFPS(void) const;

        float GetTimestep(void) const;

        uint8_t GetInterval(void) const;

    //setters
        void SetMaxFPS(uint16_t fps);

        void SetInterval(uint8_t interval);

    };

}