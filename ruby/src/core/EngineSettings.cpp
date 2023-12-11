#include "EngineSettings.hpp"

namespace Ruby
{
// getters
    uint16_t EngineSettingsStruct::GetMaxFPS(void) const
    {
        return m_maxFPS;
    }

    float EngineSettingsStruct::GetTimestep(void) const
    {
        return m_timestep;
    }


    uint8_t EngineSettingsStruct::GetInterval(void) const
    {
        return m_interval;
    }

// setters
    void EngineSettingsStruct::SetMaxFPS(uint16_t fps)
    {
        RUBY_WARNING("maxFPS changed from {} to {}(timestep also changed from {} to {})", 
                        m_maxFPS, fps, m_timestep, 1000.0 / fps);

        m_maxFPS = fps;
        m_timestep = 1000.0f / m_maxFPS;
    }


    void EngineSettingsStruct::SetInterval(uint8_t interval)
    {
        m_interval = interval;
    }
}
