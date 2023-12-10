#pragma once

#include <utility/Definitions.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <utility>


#ifdef _NDEBUG            
    #define LOG_LEVEL                   spdlog::level::info
#else
    #define LOG_LEVEL                   spdlog::level::debug
#endif  // _NDEBUG


namespace Ruby
{
    namespace LoggerTraits
    {
        using VendorLogger      = spdlog::logger;
        using DailySink         = spdlog::sinks::daily_file_sink_mt;
        using ConsoleSink       = spdlog::sinks::stdout_color_sink_mt;
    }


    class Logger final
    {
    public:
        template<typename Tx>
        using Ptr = std::shared_ptr<Tx>;


        static Logger& GetInstance(void);

        Ptr<LoggerTraits::VendorLogger> MakeLog(void) const;

        void Init(RubyString&& pathToLogFile="RubyLog", 
                RubyString&& coreName="RubyCore");


        Logger(const Logger&)               = delete;
        Logger(Logger&&)                    = delete;
        Logger& operator=(const Logger&)    = delete;

    private:
        Logger(void) = default;

        Ptr<LoggerTraits::VendorLogger> m_logger = nullptr;
    };


    void initCoreLogger(RubyString&& path="RubyLog", RubyString&& coreName="RubyCore");


    #define RUBY_DEBUG(fmt, ...)            Logger::GetInstance().MakeLog()->debug(fmt, __VA_ARGS__);
    #define RUBY_INFO(fmt, ...)             Logger::GetInstance().MakeLog()->info(fmt, __VA_ARGS__);
    #define RUBY_WARNING(fmt, ...)          Logger::GetInstance().MakeLog()->warn(fmt, __VA_ARGS__);
    #define RUBY_ERROR(fmt, ...)            Logger::GetInstance().MakeLog()->error(fmt, __VA_ARGS__);
    #define RUBY_CRITICAL(fmt, ...)         Logger::GetInstance().MakeLog()->critical(fmt, __VA_ARGS__);
}

