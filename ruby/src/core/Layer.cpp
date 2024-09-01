#include "Layer.hpp"


namespace Ruby {
    Layer::Layer() {
        m_name = std::format("Layer {}", s_unnamedLayersCounter.load());

        s_unnamedLayersCounter.fetch_add(1);
    }

    Layer::Layer(const RubyString& name) {
        m_name = name;
    }

    RubyString Layer::GetName() const {
        return m_name;
    }
}