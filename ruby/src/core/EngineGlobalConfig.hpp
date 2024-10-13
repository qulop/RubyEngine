#pragma once

#include "WindowProps.hpp"

#include <utility/ProgramOptions.hpp>
#include <utility/Definitions.hpp>
#include <types/Singleton.hpp>
#include <types/Logger.hpp>


namespace Ruby {
    struct RUBY_API EngineGlobalConfig : Singleton<EngineGlobalConfig> {
        RUBY_DEFINE_SINGLETON(EngineGlobalConfig);

    public:
        u16 maxFPS = 120;
        const f32 timestep = 1000.0f / static_cast<f32>(maxFPS);
        const u16 interval = 1; // time step after how long fps will be calculated

        RubyString applicationDirectory; // Path to the directory where the engine executable is located
        RubyString loggerBaseDirectory; //
        VideoStruct videoConfig;

    public:
        void Init(ProgramOptions&& opts);
    };
}