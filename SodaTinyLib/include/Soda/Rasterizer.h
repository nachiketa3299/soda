#pragma once

#include "Soda/FrameBuffer.h"
#include "Soda/Vec.h"
#include "Soda/Line.h"
#include "Soda/Color.h"
#include "Soda/Triangle.h"

#include <string>

namespace Soda {

enum class DrawLineMode {
    Naive,
    Bresenham
};

struct Rasterizer {

static void PutPixel(Framebuffer& fb, const Vec2i& p, const Rgb8& c);

static void Clear(Framebuffer& fb, const Rgb8& c);

static void DrawLine(Framebuffer& fb, const Vertex2i& v1, const Vertex2i& v2, DrawLineMode m);
static void DrawLine(Framebuffer& fb, const Line2i& l, DrawLineMode m);

static void DrawTriangle(Framebuffer& fb, const Triangle2i t);

};


}
