#pragma once

#include "Soda/Color.h"

#include <vector>
#include <cstdint>

namespace Soda {

struct Framebuffer {
    Framebuffer(int w, int h);
    Framebuffer(int w, int h, const Rgb8& c);

    const int width;
    const int height;
    const int channel = 3;

    std::vector<uint8_t> buff;
};

};
