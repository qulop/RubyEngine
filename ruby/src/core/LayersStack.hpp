#pragma once

#include "Layer.hpp"
#include <utility/StdInc.hpp>


namespace Ruby {
    class RUBY_API LayersStack {
        using StorageType = std::list<Layer*>;
    public:
        using Iterator = StorageType::iterator;
        using RevIterator = StorageType::reverse_iterator;

        LayersStack();

        void PushBottomLayer(Layer* layer);
        Layer* PopBottomLayer(Layer* layer=nullptr);

        void PushTopLayer(Layer* layer);
        Layer* PopTopLayer(Layer* layer=nullptr);

        Iterator begin();
        RevIterator rbegin();

        Iterator end();
        RevIterator rend();

        ~LayersStack();

    private:
        Layer* PopLayerFromStorage(Layer* layer, Iterator begin, Iterator end);
        Layer* PopLastLayerFromStorage(Iterator barrier);

    private:
        StorageType m_layers;
        Iterator m_bottomLayersBarrier;  // points to the first top layer
    };
}