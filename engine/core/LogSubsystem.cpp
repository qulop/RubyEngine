#include "LogSubsystem.hpp"


namespace Kiwi {
    LogSubsystem::LogSubsystem(LoggerInitInfo info) {
        m_fileNameTemplate = info.fileNameTemplate.empty() ?
            DEFAULT_FILE_NAME_TEMPLATE : info.fileNameTemplate;

        m_loggerName = info.loggerCoreName.empty() ?
            DEFAULT_LOGGER_NAME_TEMPLATE : info.loggerCoreName;

        m_loggerPathDir = std::move(info.loggerPathDirectory);
    }

    bool LogSubsystem::Init() {
        Super::Init();

        if (!std::filesystem::exists(m_loggerPathDir)) {
            std::error_code ec;
            if (!std::filesystem::create_directory(m_loggerPathDir, ec)) {
                Console::WriteLine("Failed to create logger directory: {}",
                    ec.message()
                );

                return false;
            }
        }

        Path logFilePath = m_loggerPathDir / m_fileNameTemplate;

        auto&& consoleSink = MakeShared<spdlog::sinks::ansicolor_stdout_sink_mt>(
            spdlog::color_mode::always
        );
        consoleSink->set_pattern("<%m-%d-%Y %H:%M:%S> %^[%l]: %v%$");
        consoleSink->set_color(spdlog::level::debug, consoleSink->blue);
        consoleSink->set_color(spdlog::level::info, consoleSink->green);
        consoleSink->set_color(spdlog::level::warn, consoleSink->yellow);
        consoleSink->set_color(spdlog::level::err, consoleSink->red);
        consoleSink->set_color(spdlog::level::critical, consoleSink->magenta);

        auto&& dailySink = MakeShared<spdlog::sinks::daily_file_sink_mt>(
            logFilePath.string(),
            1,  // 01:00 AM
            0
        );
        dailySink->set_pattern("[%l] <%m-%d-%Y %H:%M:%S> - [thread: %t] [PID: %P]: %v");


        Vector<spdlog::sink_ptr> sinks = { std::move(consoleSink), std::move(dailySink) };

        m_logger = MakeShared<spdlog::logger>(m_loggerName.data(), sinks.begin(), sinks.end());
        m_logger->set_level(KIWI_LOG_LEVEL);
        m_logger->flush_on(KIWI_LOG_LEVEL);
        spdlog::register_logger(m_logger);

        return true;

        #undef LOG_LEVEL
    }

    void LogSubsystem::Log(ELogLevel lvl, const String& msg) const {
        KIWI_ASSERT_BASIC(IsInitialized());

        switch (lvl) {
        case ELogLevel::DEBUG_LOG:
            m_logger->debug(msg); break;
        case ELogLevel::INFO_LOG:
            m_logger->info(msg); break;
        case ELogLevel::WARNING_LOG:
            m_logger->warn(msg); break;
        case ELogLevel::ERROR_LOG:
            m_logger->error(msg); break;
        case ELogLevel::CRITICAL_LOG:
            m_logger->critical(msg); break;
        default:
            std::unreachable();
        }
    }

    bool LogSubsystem::IsInitialized() const {
        return m_logger != nullptr;
    }
}
