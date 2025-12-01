#include "Shader.hpp"


namespace Kiwi {
    // TODO: Remove this function. Use `Cast<String>::ToShaderStage()` instead
    Opt<EShaderStage> AShader::StringToShaderStage(StringView stageName) {
        if      (stageName == "vertex")     return EShaderStage::VERTEX;
        else if (stageName == "geometry")   return EShaderStage::GEOMETRY;
        else if (stageName == "fragment")   return EShaderStage::FRAGMENT;
        else if (stageName == "compute")    return EShaderStage::COMPUTE;

        return nullopt;
    }
}