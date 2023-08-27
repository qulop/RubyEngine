#pragma once

#include "core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ruby
{

    class Logger
    {
    public:

        static void init(const std::string& pattern);

        static std::shared_ptr<spdlog::logger> get_engine_logger(void);

        static std::shared_ptr<spdlog::logger> get_client_logger(void);
        


    private:
        static std::shared_ptr<spdlog::logger> m_engine;
        static std::shared_ptr<spdlog::logger> m_client;


    };
}
