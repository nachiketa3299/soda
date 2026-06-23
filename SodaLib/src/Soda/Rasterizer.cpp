#include "Soda/Rasterizer.h"
#include "Soda/MathUtils.h"

#include <cmath>
#include <fstream>
#include <cassert>

namespace Soda {

Rasterizer::Rasterizer(Framebuffer& fb)
    : target_ {fb} 
{ }

void Rasterizer::FillTriangle(const Triangle2f &t) {
    Vec2i boundMin {
        static_cast<int>(std::floor(std::max(0.f, std::min({ t.a.p.x, t.b.p.x, t.c.p.x })))),
        static_cast<int>(std::floor(std::max(0.f, std::min({ t.a.p.y, t.b.p.y, t.c.p.y }))))
    };
    Vec2i boundMax {
        static_cast<int>(std::ceil(std::min(static_cast<float>(target_.Width() - 1), std::max({ t.a.p.x, t.b.p.x, t.c.p.x })))),
        static_cast<int>(std::ceil(std::min(static_cast<float>(target_.Height() - 1), std::max({ t.a.p.y, t.b.p.y, t.c.p.y })))),
    };

    float area2 = Edgef(t.a.p, t.b.p, t.c.p);

    for (int x = boundMin.x; x <= boundMax.x; ++x) {
        for (int y = boundMin.y; y <= boundMax.y; ++y) {
            Vec2f center { x + .5f, y + .5f };

            float w0 = Edgef(t.a.p, t.b.p, center);
            float w1 = Edgef(t.b.p, t.c.p, center);
            float w2 = Edgef(t.c.p, t.a.p, center);

            bool isInside 
                = (w0 >= 0 && w1 >= 0 && w2 >= 0)
                || (w0 <= 0 && w1 <= 0 && w2 <= 0);
            
            if (!isInside) {
                continue;
            }

            float alpha = w1 / area2;
            float beta = w2 / area2;
            float gamma = w0 / area2;

            Color4f c = {
                alpha * t.a.c.r + beta * t.b.c.r + gamma * t.c.c.r,
                alpha * t.a.c.g + beta * t.b.c.g + gamma * t.c.c.g,
                alpha * t.a.c.b + beta * t.b.c.b + gamma * t.c.c.b,
                alpha * t.a.c.a + beta * t.b.c.a + gamma * t.c.c.a,
            };

            target_.Blend({ x, y }, c);
        }
    }
}

void Rasterizer::DrawMesh(const Mesh& mesh, const Mat4f& mvp) {
    const float w = static_cast<float>(target_.Width());
    const float h = static_cast<float>(target_.Height());

    for (const Face& f: mesh.f) {
        const Vertex3f* in[3] {
            &mesh.v[f.a],
            &mesh.v[f.b],
            &mesh.v[f.c],
        };

        Vertex2f out[3];
        for (int i = 0; i < 3; ++i) {
            Vec3f p = in[i]->p;
            Vec4f clip = mvp * Vec4f {
                p.x, p.y, p.z, 1.f
            };

            Vec3f ndc {
                clip.x / clip.w,
                clip.y / clip.w,
                clip.z / clip.w
            };

            float sx = (ndc.x * .5f + .5f) * w;
            float sy = (.5f - ndc.y * .5f) * h;
            out[i] = Vertex2f{ .p = { sx, sy }, .c = in[i]->c };
        }

        FillTriangle(Triangle2f { out[0], out[1], out[2] });
    }
}

void LegacyRasterizer::PutPixel(FramebufferLegacy &fb, const Vec2i &p, const Rgb8 &c)
{
    assert(0 <= p.x && p.x <= fb.width);
    assert(0 <= p.y && p.y <= fb.height);

    size_t idx = 3 * (p.x + fb.width * p.y);

    fb.buff[idx + 0] = c.r;
    fb.buff[idx + 1] = c.g;
    fb.buff[idx + 2] = c.b;
}

void LegacyRasterizer::Clear(FramebufferLegacy& fb, const Rgb8& c) {
    for (int h = 0; h < fb.height; ++h) {
        for (int w = 0; w < fb.width; ++w) {
            PutPixel(fb, {w, h}, c);
        }
    }
}

void drawLineNaive(
    FramebufferLegacy& fb, 
    const Vertex2i& v1, 
    const Vertex2i& v2
) {
    int dx = v2.p.x - v1.p.x;
    int dy = v2.p.y - v1.p.y;

    int step = std::max(std::abs(dx), std::abs(dy));

    for (int i = 0; i <= step; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(step);

        float x = v1.p.x + dx * t;
        float y = v1.p.y + dy * t;

        int nx = static_cast<int>(std::floor(x));
        int ny = static_cast<int>(std::floor(y));

        Rgb8 c = LerpRgb8(v1.c, v2.c, t);
        LegacyRasterizer::PutPixel(fb, {nx, ny}, c);
    }

    return;
}

void drawLineBresenham(
    FramebufferLegacy& fb, 
    const Vertex2i& v1, 
    const Vertex2i& v2
) {
    int x = v1.p.x;
    int y = v1.p.y;

    int dx =  std::abs(v2.p.x - v1.p.x);
    int dy = -std::abs(v2.p.y - v1.p.y);

    int sx = v1.p.x < v2.p.x ? 1 : -1;
    int sy = v1.p.y < v2.p.y ? 1 : -1;

    int err = dx + dy;

    while (true) {
        LegacyRasterizer::PutPixel(fb, {x, y}, v1.c);

        if (x == v2.p.x && y == v2.p.y) {
            break;
        }

        int e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y += sy;
        }
    }
}

void LegacyRasterizer::DrawLine(
    FramebufferLegacy& fb, 
    const Line2i& l, 
    DrawLineMode m
) {
    LegacyRasterizer::DrawLine(fb, l.s, l.e, m);

    return;
}

void LegacyRasterizer::DrawLine(
    FramebufferLegacy& fb, 
    const Vertex2i& v1, 
    const Vertex2i& v2, 
    DrawLineMode m
) {
    switch (m) {
        default:
        case DrawLineMode::Naive: drawLineNaive(fb, v1, v2); break;
        case DrawLineMode::Bresenham: drawLineBresenham(fb, v1, v2); break;
    }

    return;
}

void LegacyRasterizer::DrawTriangle(
    FramebufferLegacy& fb, 
    const Triangle2i t
) {
    Vec2i min = Vec2i {
        std::max(0, std::min({ t.a.p.x, t.b.p.x, t.c.p.x })),
        std::max(0, std::min({ t.a.p.y, t.b.p.y, t.c.p.y }))
    };

    Vec2i max = Vec2i {
        std::min(std::max({ t.a.p.x, t.b.p.x, t.c.p.x }), fb.width - 1),
        std::min(std::max({ t.a.p.y, t.b.p.y, t.c.p.y }), fb.height - 1)
    };

    float area2 = static_cast<float>(Edgei(t.a.p, t.b.p, t.c.p));

    for (int y = min.y; y <= max.y; ++y) {
        for (int x = min.x; x <= max.x; ++x) {
            Vec2i p { x, y };

            int w0 = Edgei(t.a.p, t.b.p, p);
            int w1 = Edgei(t.b.p, t.c.p, p);
            int w2 = Edgei(t.c.p, t.a.p, p);

            bool isInside =
                (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0);
            
            if (!isInside) {
                continue;
            }
            
            float alpha = w1 / area2;
            float beta = w2 / area2;
            float gamma = w0 / area2;

            uint8_t r = alpha * t.a.c.r + beta * t.b.c.r + gamma * t.c.c.r;
            uint8_t g = alpha * t.a.c.g + beta * t.b.c.g + gamma * t.c.c.g;
            uint8_t b = alpha * t.a.c.b + beta * t.b.c.b + gamma * t.c.c.b;

            PutPixel(fb, p, { r, g, b });
        }
    }
}

};
