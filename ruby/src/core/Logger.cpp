#include "Logger.hpp"
#include <spdlog/common.h>

namespace Ruby
{
    uint16_t fromRGBto16Bit(uint8_t red, uint8_t green, uint8_t blue)
    {
        auto rMask = (((31 * (red + 4)) / 255) << 11);
        auto gMask = (((63 * (green + 2)) / 255) << 5);
        auto bMask = ((31 * (blue + 4)) / 255);

        return rMask | gMask | bMask;
    }


    Logger& Logger::GetInstance(void)
    {
        static Logger log;

        return log;
    }


    Logger::Ptr<LoggerTraits::VendorLogger> Logger::MakeLog(void) const
    {
        RUBY_ASSERT(m_logger != nullptr && "Logger cannot be empty: You must first call Logger::Init() before making log!");

        return m_logger;
    }    


    void Logger::Init(RubyString&& pathToLogFile, RubyString&& coreName)
    {
        auto console = std::make_shared<LoggerTraits::ConsoleSink>(spdlog::color_mode::always);
        console->set_pattern("<%m-%d-%Y %H:%M:%S> %^[%l]: %v%$");

        
        console->set_color(spdlog::level::debug, BLUE);
        console->set_color(spdlog::level::info, GREEN);
        console->set_color(spdlog::level::warn, YELLOW);
        console->set_color(spdlog::level::err, RED);
        console->set_color(spdlog::level::critical, BLACK);


        // it will create new log file every 01:00 am
        auto daily = std::make_shared<LoggerTraits::DailySink>(std::move(pathToLogFile), 1, 0);
        daily->set_pattern("[%l] <%m-$d-%Y %H:%M:%S> - [thread: %t] [line: %#]: %v");


        std::vector<spdlog::sink_ptr> sinks = { std::move(console) }; //, std::move(daily) };

        m_logger = std::make_shared<LoggerTraits::VendorLogger>(std::move(coreName), sinks.begin(), sinks.end());

        m_logger->set_level(LOG_LEVEL);
        m_logger->flush_on(LOG_LEVEL);
        spdlog::register_logger(m_logger);
    }    



    void initCoreLogger(RubyString&& path, RubyString&& coreName)
    {
        Logger::GetInstance().Init(std::move(path), std::move(coreName));
    }
}

