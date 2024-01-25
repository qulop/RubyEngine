#include "EngineSettings.hpp"

namespace Ruby
{
// getters
    u16 EngineSettingsStruct::GetMaxFPS(void) const
    {
        return m_maxFPS;
    }

    double EngineSettingsStruct::GetTimestep(void) const
    {
        return m_timestep;
    }


    u8 EngineSettingsStruct::GetInterval(void) const
    {
        return m_interval;
    }

// setters
    void EngineSettingsStruct::SetMaxFPS(u16 fps)
    {
        RUBY_WARNING("maxFPS changed from {} to {}(timestep also changed from {} to {})", 
                        m_maxFPS, fps, m_timestep, 1000.0 / fps);

        m_maxFPS = fps;
        m_timestep = 1000.0f / m_maxFPS;
    }


    void EngineSettingsStruct::SetInterval(u8 interval)
    {
        m_interval = interval;
    }
}
