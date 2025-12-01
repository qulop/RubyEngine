#include "Layer.hpp"


namespace Kiwi {
    static std::atomic<i64> s_unnamedLayersCounter = 0;


    ALayer::ALayer() {
        m_name = std::format("Layer {}", s_unnamedLayersCounter.load());

        s_unnamedLayersCounter.fetch_add(1);
    }

    ALayer::ALayer(const String& name) {
        m_name = name;
    }

    String ALayer::GetName() const {
        return m_name;
    }
}