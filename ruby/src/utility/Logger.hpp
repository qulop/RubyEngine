#pragma once

#ifdef RUBY_MSVC_USED
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <utility/Definitions.hpp>
#include <utility/Singleton.hpp>

#include <utility>


namespace Ruby
{
    namespace LoggerTraits
    {
        using VendorLogger      = spdlog::logger;
        using DailySink         = spdlog::sinks::daily_file_sink_mt;
        using ConsoleSink       = spdlog::sinks::stdout_color_sink_mt;

        const RubyString defaultPath = "logs/log-from.txt";
        const RubyString defaultName = "RubyCore";
    }


    class Logger final : public Singleton<Logger>
    {
        DEFINE_SINGLETON(Logger);
    
    public:
        template<typename Tx>
        using Ptr = std::shared_ptr<Tx>;

        RUBY_NODISCARD Ptr<LoggerTraits::VendorLogger> MakeLog() const;

        void Init(const RubyString& pathToLogFile=LoggerTraits::defaultPath, 
                    const RubyString& coreName=LoggerTraits::defaultName);

        private:
            Ptr<LoggerTraits::VendorLogger> m_logger = nullptr;
    };
}

#define RUBY_DEBUG(...)            Ruby::Logger::GetInstance().MakeLog()->debug(__VA_ARGS__)
#define RUBY_INFO(...)             Ruby::Logger::GetInstance().MakeLog()->info(__VA_ARGS__)
#define RUBY_WARNING(...)          Ruby::Logger::GetInstance().MakeLog()->warn(__VA_ARGS__)
#define RUBY_ERROR(...)            Ruby::Logger::GetInstance().MakeLog()->error(__VA_ARGS__)
#define RUBY_CRITICAL(...)         Ruby::Logger::GetInstance().MakeLog()->critical(__VA_ARGS__)

#ifdef RUBY_MSVC_USED
    #pragma warning(pop)
#endif
