#include "Logger.hpp"

namespace Ruby
{
    // std::shared_ptr<Logger::DailySink> Logger::m_sink = std::make_shared<Logger::DailySink>(
    //             "logs/rvn_log.log", 1, 0);
    
    // std::shared_ptr<Logger::VendorLogger> Logger::m_engine = std::make_shared<Logger::VendorLogger>(
    //             "CORE", Logger::m_sink);
    
    // std::shared_ptr<Logger::VendorLogger> Logger::m_client = std::make_shared<Logger::VendorLogger>(
    //             "CLIENT", Logger::m_sink);


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
        auto console = std::make_shared<LoggerTraits::ConsoleSink>();
        console->set_level(LOG_LEVEL);
        console->set_pattern("<%m-%d-%Y %H:%M:%S> [%l]: %v");
        
        console->set_color(spdlog::level::debug, fromRGBto16Bit(0, 0, 255));        // Blue
        console->set_color(spdlog::level::info, fromRGBto16Bit(0, 255, 0));         // Green
        console->set_color(spdlog::level::warn, fromRGBto16Bit(255, 165, 0));       // Orange 
        console->set_color(spdlog::level::err, fromRGBto16Bit(255, 0, 0));          // Red
        console->set_color(spdlog::level::critical, fromRGBto16Bit(128, 0, 0));     // Maroon(dark red)

        // it will create new log file every 01:00 am
        auto daily = std::make_shared<LoggerTraits::DailySink>(std::move(pathToLogFile), 1, 0);
        daily->set_level(LOG_LEVEL);
        daily->set_pattern("[%l] <%m-$d-%Y %H:%M:%S> - [thread: %t] [line: %#]: %v");

        std::vector<spdlog::sink_ptr> sinks = { console, daily };


        m_logger = std::make_shared<LoggerTraits::VendorLogger>(std::move(coreName), sinks.begin(), sinks.end());

        m_logger->flush_on(LOG_LEVEL);
        spdlog::initialize_logger(m_logger);
    }    



    void initCoreLogger(RubyString&& path, RubyString&& coreName)
    {
        Logger::GetInstance().Init(std::move(path), std::move(coreName));
    }
}

