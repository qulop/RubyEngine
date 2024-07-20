#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>

namespace Ruby {

    struct RUBY_API EngineSettingsStruct {
    private:
        u8 m_maxFPS = 120;
        double m_timestep = 1000.0f / m_maxFPS;
        u16 m_interval = 1; // time step after how long fps will be caclucalted

    public:
        RUBY_NODISCARD u16 GetMaxFPS() const;
        RUBY_NODISCARD double GetTimestep() const;
        RUBY_NODISCARD u16 GetInterval() const;

        void SetMaxFPS(u8 fps);
        void SetInterval(u8 interval);
    };

}