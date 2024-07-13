#include "LayersStack.hpp"


namespace Ruby {

    void LayersStack::PushBottomLayer(Layer* layer) {
        auto iter = std::find(begin(), m_bottomLayersBarrier, layer);
        if (iter != m_bottomLayersBarrier)  // if layer already exists
            return;

        layer->OnAttach();
        m_layers.emplace(m_bottomLayersBarrier, layer);
        m_bottomLayersBarrier++;
    }

    Layer* LayersStack::PopBottomLayer(Layer* layer) {
        if (!layer)
            return PopLastLayerFromStorage(m_bottomLayersBarrier);

        return PopLayerFromStorage(layer, begin(), m_bottomLayersBarrier);
    }

    void LayersStack::PushTopLayer(Layer* layer) {
        layer->OnAttach();
        m_layers.emplace_back(layer);

        if (m_bottomLayersBarrier == end())
            m_bottomLayersBarrier = begin();
    }

    Layer* LayersStack::PopTopLayer(Layer* layer) {
        if (!layer)
            return PopLastLayerFromStorage(end());

        return PopLayerFromStorage(layer, m_bottomLayersBarrier, end());
    }

    LayersStack::Iterator LayersStack::begin() {
        return m_layers.begin();
    }

    LayersStack::Iterator LayersStack::end() {
        return m_layers.end();
    }

    LayersStack::~LayersStack() {
        for (auto* l : m_layers)
            delete l;
    }



    Layer* LayersStack::PopLayerFromStorage(Layer* layer, Iterator begin, Iterator end) {
        RUBY_ASSERT_1(layer != nullptr);

        auto iter = std::find(begin, end, layer);
        if (iter == end)
            return nullptr;

        layer->OnDetach();
        m_layers.erase(iter);

        return layer;
    }

    Layer* LayersStack::PopLastLayerFromStorage(Iterator barrier) {
        // if there are no layers or no bottom layers
        if (m_layers.empty() || barrier == begin())
            return nullptr;

        auto it = barrier - 1;
        auto tmp = *it;
        m_layers.erase(it);

        tmp->OnDetach();
        return tmp;
    }
}
