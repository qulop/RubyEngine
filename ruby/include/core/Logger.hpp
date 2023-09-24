#pragma once

#include "Core.hpp"
#include <chrono>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <utility>


namespace Ruby
{
    namespace chrono = std::chrono;


    class Logger
    {
    public:
        using VendorLogger  = spdlog::logger;
        using DailySink     = spdlog::sinks::daily_file_sink_mt;

        Logger(void) = delete;

        static void Init(void);
        static std::shared_ptr<VendorLogger> GetCoreLogger(void);
        static std::shared_ptr<VendorLogger> GetClientLogger(void);

    private:
        static std::shared_ptr<DailySink>    m_sink;
        static std::shared_ptr<VendorLogger> m_engine;
        static std::shared_ptr<VendorLogger> m_client;


    };

    // Isn't visible for Clients
    #define CORE_DEBUG(fmt, ...)            Logger::GetCoreLogger()->debug(fmt, __VA_ARGS__);
    #define CORE_INFO(fmt, ...)             Logger::GetCoreLogger()->info(fmt, __VA_ARGS__);
    #define CORE_ERROR(fmt, ...)            Logger::GetCoreLogger()->error(fmt, __VA_ARGS__);
    #define CORE_CRITICAL(fmt, ...)         Logger::GetCoreLogger()->critical(fmt, __VA_ARGS__);
    #define CORE_FLUSH()                    Logger::GetCoreLogger()->flush();
    // ------------------------


    template<typename... Args>
    void RUBY_API debug(const std::string& fmt, Args&&... args);

    template<typename... Args>
    void RUBY_API info(const std::string& fmt, Args&&... args);

    template<typename... Args>
    void RUBY_API error(const std::string& fmt, Args&&... args);

    template<typename... Args>
    void RUBY_API critical(const std::string& fmt, Args&&... args);
}

