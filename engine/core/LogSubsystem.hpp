#pragma once

#include <core/Object.hpp>
#include <core/LogLevel.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>


namespace Kiwi {
    struct LoggerInitInfo {
        Path loggerPathDirectory;
        StringView fileNameTemplate;
        StringView loggerCoreName;
    };


    class LogSubsystem final : public ASubsystem {
        KIWI_CREATE_OBJECT(LogSubsystem, ASubsystem)

    private:
        static constexpr StringView DEFAULT_FILE_NAME_TEMPLATE = "log-from.log";
        static constexpr StringView DEFAULT_LOGGER_NAME_TEMPLATE = "KiwiEngine";
        static constexpr StringView DEFAULT_LOGS_DIRECTORY_NAME = "logs";

    private:
        using LoggerPtrType = SharedPtr<spdlog::logger>;

    public:
        explicit LogSubsystem(LoggerInitInfo info);

    public:
        bool Init() override;


        template<typename... Args>
        void Log(ELogLevel lvl, std::format_string<Args...> fmt, Args... args) const {
            Log(lvl, std::format(fmt, std::forward<Args>(args)...));
        }

        void Log(ELogLevel lvl, const String& msg) const;


        KIWI_NODISCARD bool IsInitialized() const;


        ~LogSubsystem() override = default;

    private:
        LoggerPtrType m_logger = nullptr;

        String m_fileNameTemplate;
        String m_loggerName;
        Path m_loggerPathDir;
    };
}