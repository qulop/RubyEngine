#pragma once

#include "Layer.hpp"
#include <utility/StdInc.hpp>


namespace Ruby {
    class RUBY_API LayersStack {
        using StorageType = std::vector<Layer*>;
    public:
        using Iterator = StorageType::iterator;

        LayersStack() = default;

        void PushBottomLayer(Layer* layer);
        Layer* PopBottomLayer(Layer* layer=nullptr);

        void PushTopLayer(Layer* layer);
        Layer* PopTopLayer(Layer* layer=nullptr);

        Iterator begin();
        Iterator end();

        ~LayersStack();

    private:
        Layer* PopLayerFromStorage(Layer* layer, Iterator begin, Iterator end);
        Layer* PopLastLayerFromStorage(Iterator barrier);

    private:
        StorageType m_layers;
        Iterator m_bottomLayersBarrier = m_layers.end();  // points to the first top layer
    };
}