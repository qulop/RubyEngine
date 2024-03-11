#pragma once

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include "EngineSettings.hpp"
#include "Timer.hpp"

#include <window/WindowAgent.hpp>

#include <algorithm>


namespace Ruby
{
    class RUBY_API RubyApp
    {
    protected:
        RubyApp(void);
        
        explicit RubyApp(VideoStruct& va);

    protected:
        EngineSettingsStruct rubySettings;

    public:
        template<typename Tx, typename... Args>
            requires std::is_base_of_v<RubyApp, Tx>
        static std::unique_ptr<Tx> CreateApp(Args&&... args)
        { return std::make_unique<Tx>(std::forward<Args>(args)...); }

        u8 Mainloop(void);

        void Finish(void);

        virtual void Update(void) = 0;

        void SetFramerate(u8 newFramerate);

        virtual ~RubyApp(void);

    private:
        u16 GetFPS(void);

    private:
        std::unique_ptr<WindowAgent> m_window;
        bool m_isRunning = true; 
    };

}