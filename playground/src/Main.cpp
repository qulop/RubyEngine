#include "PlaygroundLayer.hpp"


int main(int argc, char** argv) {
    Ruby::VideoStruct va;
    va.title = "Demo Application";
    va.isFullScreened = false;

    Ruby::CommandLineArgs args{ argc, argv };

    auto app = Ruby::MakePtr<Ruby::Application>(args, va);

    auto* one = new PlaygroundLayer;
    auto* two = new PlaygroundLayer;

    app->PushTopLayer(two);
    app->PushBottomLayer(one);

    if (app->Start())
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}