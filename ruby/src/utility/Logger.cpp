#include <utility/Logger.hpp>

namespace Ruby {
    Logger::Ptr<LoggerTraits::VendorLogger> Logger::MakeLog() const {
        RUBY_ASSERT(m_logger != nullptr, "Logger cannot be empty: You must first call Logger::Init() before making log!");

        return m_logger;
    }    


    void Logger::Init(const RubyString& pathToLogFile, const RubyString& coreName) {
        auto console = std::make_shared<LoggerTraits::ConsoleSink>(spdlog::color_mode::always);
        console->set_pattern("<%m-%d-%Y %H:%M:%S> %^[%l]: %v%$");

        
        console->set_color(spdlog::level::debug, 1);        // Blue
        console->set_color(spdlog::level::info, 2);         // Green
        console->set_color(spdlog::level::warn, 6);         // Yellow
        console->set_color(spdlog::level::err, 4);          // Red
        console->set_color(spdlog::level::critical, 4);     // Red


        // it will create new log file every 01:00 am
        auto daily = std::make_shared<LoggerTraits::DailySink>(pathToLogFile, 1, 0);
        daily->set_pattern("[%l] <%m-%d-%Y %H:%M:%S> - [thread: %t] [PID: %P]: %v");


        std::vector<spdlog::sink_ptr> sinks = { std::move(console), std::move(daily) };

        m_logger = std::make_shared<LoggerTraits::VendorLogger>(coreName, sinks.begin(), sinks.end());

        m_logger->set_level(LOG_LEVEL);
        m_logger->flush_on(LOG_LEVEL);
        spdlog::register_logger(m_logger);

        #undef LOG_LEVEL
    }    
}

