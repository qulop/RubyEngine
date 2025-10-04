#pragma once

#include "Layer.hpp"
#include <types/StdInc.hpp>


namespace Ruby {
    class RUBY_API LayersStack {
        using StorageType = std::list<ALayer*>;
    public:
        using Iterator = StorageType::iterator;
        using RevIterator = StorageType::reverse_iterator;

        LayersStack();

        RUBY_NODISCARD size_t Size() const;

        void PushBottomLayer(ALayer* layer);
        ALayer* PopBottomLayer(ALayer* layer=nullptr);

        void PushTopLayer(ALayer* layer);
        ALayer* PopTopLayer(ALayer* layer=nullptr);

        RUBY_NODISCARD Iterator begin();
        RUBY_NODISCARD RevIterator rbegin();

        RUBY_NODISCARD Iterator end();
        RUBY_NODISCARD RevIterator rend();

        ~LayersStack();

    private:
        ALayer* PopLayerFromStorage(ALayer* layer, Iterator begin, Iterator end);
        ALayer* PopLastLayerFromStorage(Iterator barrier);

    private:
        StorageType m_layers;
        Iterator m_bottomLayersBarrier;  // points to the first top layer
    };
}