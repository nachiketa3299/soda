#pragma once

#include "Soda/Rasterizer.h"
#include "Soda/Window.h"
#include "Soda/Clock.h"

#include <string_view>
#include <functional>

namespace Soda {

class App {
public:
    App(std::string_view title, int w, int h);
    void Run(std::function<void(float dt, Rasterizer&)> frame);

private:
    Window window_;
    Framebuffer fb_;
    Rasterizer rt_;
    Clock clock_;
};

}