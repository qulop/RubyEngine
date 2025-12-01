#pragma once

#include <utility/Definitions.hpp>
#include <events/IEvent.hpp>


namespace Kiwi {
    KIWI_ABSTRACT class KIWI_API ALayer {
    public:
        ALayer();
        ALayer(const String& name);  // NOLINT

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnEvent(IEvent* event) = 0;
        virtual void Update() = 0;

        KIWI_NODISCARD String GetName() const;

        virtual ~ALayer() = default;

    private:
        String m_name;
    };
}