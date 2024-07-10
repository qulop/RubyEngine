#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


namespace Ruby::Linux
{
    // Will return X as first and Y as second
    std::pair<i32, i32> getScreenResolution() noexcept;
}