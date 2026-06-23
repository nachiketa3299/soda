#include "Soda/MathUtils.h"
#include "Soda/Framebuffer.h"
#include "Soda/Rasterizer.h"
#include "Soda/Color.h"

#include <cassert>

namespace Soda {

Framebuffer::Framebuffer(int width, int height)
    : width_(width), height_(height)
    , pixels_(width * height)
{
    Clear(ToColor4f(Rgba8::Black));
}

Framebuffer::Framebuffer(int width, int height, const Color4f &c) 
    : Framebuffer(width, height)
{
    Clear(c);
}

Rgba8 Framebuffer::At(const Vec2i &p)
{
    assert(IsInBound(p));
    return pixels_[Index(p)];
}

void Framebuffer::Set(const Vec2i& p, const Color4f& c) {
    assert(IsInBound(p));
    pixels_[Index(p)] = ToRgba8(c);
}

void Framebuffer::Blend(const Vec2i& p, const Color4f& src) {
    assert(IsInBound(p));
    const Color4f dst = ToColor4f(At(p));

    pixels_[Index(p)] = ToRgba8(Lerp(dst, src, src.a));
}

void Framebuffer::Clear(const Color4f& c) {
    for (int h = 0; h < height_; ++h) {
        for (int w = 0; w < width_; ++w) {
            Set(Vec2i { w, h }, c);
        }
    }
}

size_t Framebuffer::Index(const Vec2i &p) const {
    return static_cast<size_t>(p.x + width_ * p.y);
}

bool Framebuffer::IsInBound(const Vec2i &p) const {
    return 0 <= p.x && p.x < width_ && 0 <= p.y && p.y < height_;
}

FramebufferLegacy::FramebufferLegacy(int w, int h)
    : width(w), height(h), buff(width * height * channel)
{ }

FramebufferLegacy::FramebufferLegacy(int w, int h, const Rgb8& c)
    : FramebufferLegacy(w, h)
{
    LegacyRasterizer::Clear(*this, c);
}

}

