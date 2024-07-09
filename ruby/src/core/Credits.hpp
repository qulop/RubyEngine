#pragma once

#include <utility/TypeTraits.hpp>
#include <utility/StdInc.hpp>


namespace Ruby
{
    RubyString getEngineCredits()
    {
        std::stringstream ss;

        ss << "RubyEngine DEV.V\n";
        ss << "Directors by inspiration:\n";
        ss << "   * Amy\n";
        ss << "   * Clara\n";
        ss << "   * Victoria\n";
        ss << "Developed by Me(Qulop)";
        ss << "---------";
        ss << "Special thanks to the next libraries: FreeType, Glad, GLFW, GLM, Json(by Nlohmann), SpdLog, Stb.\n";
        ss << "---------";

        return ss.str();
    }
}