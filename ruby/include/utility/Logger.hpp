#pragma once

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
    }


    class Logger final : public Singleton<Logger>
    {
    public:
        DEFINE_SINGLETON(Logger);

        template<typename Tx>
        using Ptr = std::shared_ptr<Tx>;

        Ptr<LoggerTraits::VendorLogger> MakeLog(void) const;

        void Init(const RubyString& pathToLogFile="RubyLog", const RubyString& coreName="RubyCore");

    private:
        Logger(void) = default;

        Ptr<LoggerTraits::VendorLogger> m_logger = nullptr;
    };


    #define RUBY_DEBUG(fmt, ...)            Logger::GetInstance().MakeLog()->debug(fmt, __VA_ARGS__)
    #define RUBY_INFO(fmt, ...)             Logger::GetInstance().MakeLog()->info(fmt, __VA_ARGS__)
    #define RUBY_WARNING(fmt, ...)          Logger::GetInstance().MakeLog()->warn(fmt, __VA_ARGS__)
    #define RUBY_ERROR(fmt, ...)            Logger::GetInstance().MakeLog()->error(fmt, __VA_ARGS__)
    #define RUBY_CRITICAL(fmt, ...)         Logger::GetInstance().MakeLog()->critical(fmt, __VA_ARGS__)
}

