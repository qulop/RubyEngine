#pragma once

#ifdef KIWI_MSVC_USED
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

#include <utility/Definitions.hpp>
#include <types/Singleton.hpp>

#include "StdInc.hpp"



namespace Kiwi::Details::LegacyLoggerDetails {
    using VendorLogger      = spdlog::logger;
    using DailySink         = spdlog::sinks::daily_file_sink_mt;
    using ConsoleSink       = spdlog::sinks::ansicolor_stdout_sink_mt;

    extern const char* logsDirectory;
    extern const char* defaultFileName;
    extern const char* defaultLoggerName;
}

namespace Kiwi {
    class KIWI_API LegacyLogger final : public Singleton<LegacyLogger> {
        KIWI_DEFINE_SINGLETON(LegacyLogger);

    public:
        using LoggerPtr = SharedPtr<Details::LegacyLoggerDetails::VendorLogger>;

    public:
        KIWI_DEPRECATED static void Init(Path loggerPath,
                       const char* fileName = Details::LegacyLoggerDetails::defaultFileName,
                       const char* coreName = Details::LegacyLoggerDetails::defaultLoggerName);

    public:
        KIWI_DEPRECATED KIWI_NODISCARD LoggerPtr GetLogger() const;
        KIWI_DEPRECATED KIWI_NODISCARD bool IsInitialized() const;

    private:
        LoggerPtr m_logger = nullptr;
    };
}


#define KIWI_DEBUG(...)            Kiwi::LegacyLogger::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define KIWI_INFO(...)             Kiwi::LegacyLogger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define KIWI_WARNING(...)          Kiwi::LegacyLogger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define KIWI_ERROR(...)            Kiwi::LegacyLogger::GetInstance().GetLogger()->error(__VA_ARGS__)
#define KIWI_CRITICAL(...)         Kiwi::LegacyLogger::GetInstance().GetLogger()->critical(__VA_ARGS__)

#ifdef KIWI_MSVC_USED
    #pragma warning(pop)
#endif
