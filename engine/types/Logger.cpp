#include "Logger.hpp"

#include <platform/Platform.hpp>
#include <utility/Assert.hpp>


namespace Kiwi::Details::LegacyLoggerDetails {
    const char* logsDirectory = "logs";
    const char* defaultFileName = "log-from.log";
    const char* defaultLoggerName = "LegacyLogger_KiwiEngine";
}

namespace Kiwi {
    void LegacyLogger::Init(Path loggerPath, const char* fileName, const char* coreName) {
        loggerPath /= Details::LegacyLoggerDetails::logsDirectory;
        if (!std::filesystem::exists(loggerPath))
            std::filesystem::create_directory(loggerPath);
        loggerPath /= fileName;

        auto& instLogger = GetInstance().m_logger;

        auto&& console = MakeShared<Details::LegacyLoggerDetails::ConsoleSink>(spdlog::color_mode::always);
        console->set_pattern("<%m-%d-%Y %H:%M:%S> %^[%l]: %v%$");


        console->set_color(spdlog::level::debug, console->blue);
        console->set_color(spdlog::level::info, console->green);
        console->set_color(spdlog::level::warn, console->yellow);
        console->set_color(spdlog::level::err, console->red);
        console->set_color(spdlog::level::critical, console->magenta);

        // it will create new log file every 01:00 am
        auto&& daily = MakeShared<Details::LegacyLoggerDetails::DailySink>(std::move(loggerPath.string()), 1, 0);
        daily->set_pattern("[%l] <%m-%d-%Y %H:%M:%S> - [thread: %t] [PID: %P]: %v");


        Vector<spdlog::sink_ptr> sinks = { std::move(console), std::move(daily) };
        instLogger = MakeShared<Details::LegacyLoggerDetails::VendorLogger>(coreName, sinks.begin(), sinks.end());

        instLogger->set_level(KIWI_LOG_LEVEL);
        instLogger->flush_on(KIWI_LOG_LEVEL);
        spdlog::register_logger(instLogger);

        #undef LOG_LEVEL
    }


    SharedPtr<Details::LegacyLoggerDetails::VendorLogger> LegacyLogger::GetLogger() const {
        KIWI_ASSERT(IsInitialized(), "Logger cannot be empty: You must first call Logger::Init() before making a log!");

        return m_logger;
    }    

    bool LegacyLogger::IsInitialized() const {
        return m_logger != nullptr;
    }
}

