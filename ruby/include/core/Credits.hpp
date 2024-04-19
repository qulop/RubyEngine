#pragma once


namespace Ruby
{
    template<typename OStream>
    void printRubyCredits(OStream stream)
    {
        stream << "RubyEngine DEV.V\n";
        stream << "Directors by inspiration:\n";
        stream << "   * Amy\n";
        stream << "   * Clara\n";
        stream << "   * Victoria\n";
        stream << "Developed by Qulop";
        stream << "---------";
        stream << "Special thanks to the next libraries: FreeType, Glad, GLFW, GLM, Json(by Nlohmann), SpdLog, Stb, Soil.\n";
        stream << "---------";
    }
}