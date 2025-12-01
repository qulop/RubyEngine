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


namespace Kiwi {
    class KIWI_API Logger;  // Declaration for critical function (see bellow)


    namespace Details::LoggerDetails {
        using VendorLogger      = spdlog::logger;
        using DailySink         = spdlog::sinks::daily_file_sink_mt;
        using ConsoleSink       = spdlog::sinks::ansicolor_stdout_sink_mt;

        extern const char* logsDirectory;
        extern const char* defaultFileName;
        extern const char* defaultLoggerName;
    }


    class KIWI_API Logger final : public Singleton<Logger> {
        KIWI_DEFINE_SINGLETON(Logger);

    public:
        using LoggerPtr = SharedPtr<Details::LoggerDetails::VendorLogger>;

    public:
        static void Init(Path loggerPath,
                       const char* fileName = Details::LoggerDetails::defaultFileName,
                       const char* coreName = Details::LoggerDetails::defaultLoggerName);

    public:
        KIWI_NODISCARD LoggerPtr GetLogger() const;
        KIWI_NODISCARD bool IsInitialized() const;

    private:
        LoggerPtr m_logger = nullptr;
    };


    namespace Details::LoggerDetails {
        void DestroyAppWithErrorBox(const String& msg);

        template<typename... Args>
        void Critical(spdlog::format_string_t<Args...> format, Args&&... args) {
            auto&& msg = fmt::format(format, std::forward<Args>(args)...);
            Logger::GetInstance().GetLogger()->critical(std::move(format), std::forward<Args>(args)...);

            DestroyAppWithErrorBox(msg);
        }

        template<typename Tx>
        void Critical(const Tx& format) {
            Logger::GetInstance().GetLogger()->critical(format);

            DestroyAppWithErrorBox(format);
        }
    }
}

#define KIWI_DEBUG(...)            Kiwi::Logger::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define KIWI_INFO(...)             Kiwi::Logger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define KIWI_WARNING(...)          Kiwi::Logger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define KIWI_ERROR(...)            Kiwi::Logger::GetInstance().GetLogger()->error(__VA_ARGS__)
#define KIWI_CRITICAL(...)         Kiwi::Details::LoggerDetails::Critical(__VA_ARGS__)

#ifdef KIWI_MSVC_USED
    #pragma warning(pop)
#endif
