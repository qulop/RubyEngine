#include "Logger.hpp"

namespace Ruby
{
    std::shared_ptr<Logger::DailySink> Logger::m_sink = std::make_shared<Logger::DailySink>(
                "logs/rvn_log.log", 1, 0);
    
    std::shared_ptr<Logger::VendorLogger> Logger::m_engine = std::make_shared<Logger::VendorLogger>(
                "CORE", Logger::m_sink);
    
    std::shared_ptr<Logger::VendorLogger> Logger::m_client = std::make_shared<Logger::VendorLogger>(
                "CLIENT", Logger::m_sink);


    void Logger::Init(void)
    {
        m_engine->set_pattern("[%l] <%m-$d-%Y %H:%M:%S> - [%n]: %v");
        m_client->set_pattern("[%l] <%m-$d-%Y %H:%M:%S> - [%n]: %v");

        m_engine->set_level(LOG_LEVEL);
        m_client->set_level(spdlog::level::info);

        m_engine->flush_on(LOG_LEVEL);
        m_client->flush_on(spdlog::level::info);

        spdlog::initialize_logger(m_engine);
        spdlog::initialize_logger(m_client);
    }

    std::shared_ptr<spdlog::logger> Logger::GetCoreLogger(void)
    { return m_engine; }
    
    std::shared_ptr<spdlog::logger> Logger::GetClientLogger(void)
    { return m_client; }


    /// debug()
    template<typename... Args>
    void RUBY_API debug(const std::string& fmt, Args&&... args)
    { Logger::GetClientLogger()->debug(fmt, std::forward<Args>(args)...); }

    template<>
    void RUBY_API debug(const std::string& fmt)
    { Logger::GetClientLogger()->debug(fmt); }
    // ---------


    // info()
    template<typename... Args>
    void RUBY_API info(const std::string& fmt, Args&&... args)
    { Logger::GetClientLogger()->info(fmt, std::forward<Args>(args)...); }

    template<>
    void RUBY_API info(const std::string& fmt)
    { Logger::GetClientLogger()->info(fmt); }
    // ---------


    // error()
    template<typename... Args>
    void RUBY_API error(const std::string& fmt, Args&&... args)
    { Logger::GetClientLogger()->error(fmt, std::forward<Args>(args)...); }

    template<>
    void RUBY_API error(const std::string& fmt)
    { Logger::GetClientLogger()->error(fmt); }
    // ---------


    // critical()
    template<typename... Args>
    void RUBY_API critical(const std::string& fmt, Args&&... args)
    { Logger::GetClientLogger()->critical(fmt, std::forward<Args>(args)...); }

    template<>
    void RUBY_API critical(const std::string& fmt)
    { Logger::GetClientLogger()->critical(fmt); }

}

