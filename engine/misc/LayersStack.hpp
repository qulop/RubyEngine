#pragma once

#include "Layer.hpp"
#include <common/StdInc.hpp>


namespace Kiwi {
    class KIWI_API LayersStack {
        using StorageType = std::list<ALayer*>;
    public:
        using Iterator = StorageType::iterator;
        using RevIterator = StorageType::reverse_iterator;

        LayersStack();

        KIWI_NODISCARD size_t Size() const;

        void PushBottomLayer(ALayer* layer);
        ALayer* PopBottomLayer(ALayer* layer=nullptr);

        void PushTopLayer(ALayer* layer);
        ALayer* PopTopLayer(ALayer* layer=nullptr);

        KIWI_NODISCARD Iterator begin();
        KIWI_NODISCARD RevIterator rbegin();

        KIWI_NODISCARD Iterator end();
        KIWI_NODISCARD RevIterator rend();

        ~LayersStack();

    private:
        ALayer* PopLayerFromStorage(ALayer* layer, Iterator begin, Iterator end);
        ALayer* PopLastLayerFromStorage(Iterator barrier);

    private:
        StorageType m_layers;
        Iterator m_bottomLayersBarrier;  // points to the first top layer
    };
}