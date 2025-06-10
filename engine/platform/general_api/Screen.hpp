#pragma once

#include <types/TypeTraits.hpp>


namespace Ruby::Platform {
    //  + `width` in the `std::pair::first`
    // + `height` in the `std::pair::second`
    std::pair<i32, i32> getScreenResolution() noexcept;


    void errorBox(std::string_view msg, std::string_view title) noexcept;
    void infoBox(std::string_view msg, std::string_view title) noexcept;
}