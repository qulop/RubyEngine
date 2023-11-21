#include "Logger.hpp"

namespace Ruby
{
    // std::shared_ptr<Logger::DailySink> Logger::m_sink = std::make_shared<Logger::DailySink>(
    //             "logs/rvn_log.log", 1, 0);
    
    // std::shared_ptr<Logger::VendorLogger> Logger::m_engine = std::make_shared<Logger::VendorLogger>(
    //             "CORE", Logger::m_sink);
    
    // std::shared_ptr<Logger::VendorLogger> Logger::m_client = std::make_shared<Logger::VendorLogger>(
    //             "CLIENT", Logger::m_sink);


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
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<LoggerTraits::ConsoleSink>());
        sinks.push_back(std::make_shared<LoggerTraits::DailySink>(std::move(pathToLogFile), 1, 0));    
        // ^^^ will create new log file every 01:00 am

        m_logger = std::make_shared<LoggerTraits::VendorLogger>(std::move(coreName), sinks.begin(), sinks.end());

        m_logger->set_pattern("[%l] <%m-$d-%Y %H:%M:%S> - [thread: %t] [%n]: %v");
        m_logger->set_level(LOG_LEVEL);

        m_logger->flush_on(LOG_LEVEL);
        spdlog::initialize_logger(m_logger);
    }    



    void initCoreLogger(RubyString&& path, RubyString&& coreName)
    {
        Logger::GetInstance().Init(std::move(path), std::move(coreName));
    }
}

