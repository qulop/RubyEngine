#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby::Linux
{
    std::pair<i32, i32> getScreenResolution() noexcept;
}