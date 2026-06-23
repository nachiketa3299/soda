#pragma once

#include "Soda/Color.h"
#include "Soda/Vec.h"

#include <vector>
#include <cstdint>

namespace Soda {

class Framebuffer {
public:
    Framebuffer(int width, int height);
    Framebuffer(int width, int height, const Color4f& c);

    Rgba8 At(const Vec2i& p);
    void Set(const Vec2i& p, const Color4f& c);
    void Blend(const Vec2i& p, const Color4f& c);

    void Clear(const Color4f& c);

    inline int Width() const { return width_; }
    inline int Height() const { return height_; }
    inline const Rgba8* Data() const { return pixels_.data(); }

private:
    size_t Index(const Vec2i& p) const;
    bool IsInBound(const Vec2i& p) const;

private:
    int width_, height_;
    std::vector<Rgba8> pixels_;
};

struct FramebufferLegacy {
    FramebufferLegacy(int w, int h);
    FramebufferLegacy(int w, int h, const Rgb8& c);

    const int width;
    const int height;
    const int channel = 3;

    std::vector<uint8_t> buff;
};

};
