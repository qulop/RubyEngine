#include <RubyEngine.hpp>
#include <cstdio>


class PlaygroundLayer : public Ruby::Layer {
public:
    PlaygroundLayer() :
        Ruby::Layer()
    { }

    void OnDetach() override {
        fprintf_s(stdout, "PlaygroundLayer::OnDetach()\n");
    }

    void OnAttach() override {
        fprintf_s(stdout, "PlaygroundLayer::OnAttach()\n");
    }

    void Update() override {
        fprintf_s(stdout, "Layer: %s\n", GetName().c_str());
    }

    ~PlaygroundLayer() override { }
};
