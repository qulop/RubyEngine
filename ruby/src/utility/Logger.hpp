#pragma once

#ifdef RUBY_MSVC_USED
    #pragma warning(push)
    #pragma warning(disable : 4996)
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <utility/Definitions.hpp>
#include <utility/Singleton.hpp>

#include <utility>


namespace Ruby {
    namespace Details::Log2 {
        using VendorLogger      = spdlog::logger;
        using DailySink         = spdlog::sinks::daily_file_sink_mt;
        using ConsoleSink       = spdlog::sinks::stdout_color_sink_mt;

        const RubyString defaultPath = "logs/log-from.txt";
        const RubyString defaultName = "RubyCore";

        void destroyApp(const RubyString& msg);
    }


    class RUBY_API Logger final : public Singleton<Logger> {
        RUBY_DEFINE_SINGLETON(Logger);

    public:
        template<typename Tx>
        using Ptr = std::shared_ptr<Tx>;

        RUBY_NODISCARD Ptr<Details::Log2::VendorLogger> GetVendorLogger() const;

        void Init(const RubyString& pathToLogFile=Details::Log2::defaultPath,
                    const RubyString& coreName=Details::Log2::defaultName);

        private:
            Ptr<Details::Log2::VendorLogger> m_logger = nullptr;
    };


    namespace Details::Log2 {
        template<typename... Args>
        void critical(spdlog::format_string_t<Args...> format, Args&&... args) {
            auto&& msg = fmt::format(format, std::forward<Args>(args)...);
            Logger::GetInstance().GetVendorLogger()->critical(std::move(format), std::forward<Args>(args)...);

            destroyApp(msg);
        }

        template<typename Tx>
        void critical(const Tx& format) {
            Logger::GetInstance().GetVendorLogger()->critical(format);

            destroyApp(format);
        }
    }
}

#define RUBY_DEBUG(...)            Ruby::Logger::GetInstance().GetVendorLogger()->debug(__VA_ARGS__)
#define RUBY_INFO(...)             Ruby::Logger::GetInstance().GetVendorLogger()->info(__VA_ARGS__)
#define RUBY_WARNING(...)          Ruby::Logger::GetInstance().GetVendorLogger()->warn(__VA_ARGS__)
#define RUBY_ERROR(...)            Ruby::Logger::GetInstance().GetVendorLogger()->error(__VA_ARGS__)
#define RUBY_CRITICAL(...)         Ruby::Details::Log2::critical(__VA_ARGS__)

#ifdef RUBY_MSVC_USED
    #pragma warning(pop)
#endif
