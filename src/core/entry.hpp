#pragma once

#include "core.hpp"

#define RUBY_INIT_FAIL  0x01
#define RUBY_EXIT       0x02


namespace Ruby
{

class RubyApp
{
public:
    RubyApp(void) = default;

    uint8_t Run(void) const noexcept;

    void Stop(void) noexcept;

private:
    bool m_running = true;
};

}