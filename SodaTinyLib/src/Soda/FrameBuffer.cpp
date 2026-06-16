#include "Soda/FrameBuffer.h"
#include "Soda/Rasterizer.h"
#include "Soda/Color.h"

namespace Soda {

Framebuffer::Framebuffer(int w, int h)
    : width(w) , height(h)
    , buff(width * height * channel)
{ }

Framebuffer::Framebuffer(int w, int h, const Rgb8& c)
    : Framebuffer(w, h)
{
    Rasterizer::Clear(*this, c);
}

}
