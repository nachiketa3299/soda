#include "PPM/FrameBuffer3.h"
#include "PPM/Renderer3.h"

namespace SodaTiny::PPM {

FrameBuffer3::FrameBuffer3(size_t w, size_t h)
    : width(w) , height(h)
    , buff(width * height * channel)
{ }

FrameBuffer3::FrameBuffer3(size_t w, size_t h, const Color8& c)
    : FrameBuffer3(w, h)
{ 
    Renderer3::Clear(*this, c);
}

}