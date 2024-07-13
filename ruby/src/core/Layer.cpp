#include "Layer.hpp"


namespace Ruby {
    static i64 s_unnamedLayersCounter = 0;


    Layer::Layer() {
        m_name = std::format("Layer {}", s_unnamedLayersCounter);

        ++s_unnamedLayersCounter;
    }

    Layer::Layer(const RubyString& name) {
        m_name = name;
    }

    RubyString Layer::GetName() const {
        return m_name;
    }
}