#pragma once

#include <memory>
#include <string_view>

#include "Soda/Framebuffer.h"

namespace Soda {

class Window {
public:
    Window(std::string_view title, int w, int h);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void PollEvents();
    bool ShouldClose() const;

    void Present(const Framebuffer& fb);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}