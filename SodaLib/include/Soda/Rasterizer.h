#pragma once

#include "Soda/Framebuffer.h"
#include "Soda/Vec.h"
#include "Soda/Line.h"
#include "Soda/Color.h"
#include "Soda/Triangle.h"
#include "Soda/Mesh.h"
#include "Soda/Mat.h"

namespace Soda {

class Rasterizer {

public:
    explicit Rasterizer(Framebuffer& fb);

    void FillTriangle(const Triangle2f& t);
    void DrawMesh(const Mesh& m, const Mat4f& mvp);

private:
    Framebuffer& target_;
};

enum class DrawLineMode {
    Naive,
    Bresenham
};

struct LegacyRasterizer {

static void PutPixel(FramebufferLegacy& fb, const Vec2i& p, const Rgb8& c);

static void Clear(FramebufferLegacy& fb, const Rgb8& c);

static void DrawLine(FramebufferLegacy& fb, const Vertex2i& v1, const Vertex2i& v2, DrawLineMode m);
static void DrawLine(FramebufferLegacy& fb, const Line2i& l, DrawLineMode m);

static void DrawTriangle(FramebufferLegacy& fb, const Triangle2i t);

};


}
