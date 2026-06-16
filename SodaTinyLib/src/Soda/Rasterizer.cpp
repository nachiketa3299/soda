#include "Soda/Rasterizer.h"
#include "Soda/MathUtils.h"

#include <cmath>
#include <fstream>
#include <cassert>

namespace Soda {

void Rasterizer::PutPixel(Framebuffer& fb, const Vec2i& p, const Rgb8& c) {
    assert(0 <= p.x && p.x <= fb.width);
    assert(0 <= p.y && p.y <= fb.height);

    size_t idx = 3 * (p.x + fb.width * p.y);

    fb.buff[idx + 0] = c.r;
    fb.buff[idx + 1] = c.g;
    fb.buff[idx + 2] = c.b;
}

void Rasterizer::Clear(Framebuffer& fb, const Rgb8& c) {
    for (int h = 0; h < fb.height; ++h) {
        for (int w = 0; w < fb.width; ++w) {
            PutPixel(fb, {w, h}, c);
        }
    }
}

void drawLineNaive(
    Framebuffer& fb, 
    const Vertex2i& v1, 
    const Vertex2i& v2
) {
    int dx = v2.pos.x - v1.pos.x;
    int dy = v2.pos.y - v1.pos.y;

    int step = std::max(std::abs(dx), std::abs(dy));

    for (int i = 0; i <= step; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(step);

        float x = v1.pos.x + dx * t;
        float y = v1.pos.y + dy * t;

        int nx = static_cast<int>(std::floor(x));
        int ny = static_cast<int>(std::floor(y));

        Rgb8 c = LerpRgb8(v1.col, v2.col, t);
        Rasterizer::PutPixel(fb, {nx, ny}, c);
    }
}

void drawLineBresenham(
    Framebuffer& fb, 
    const Vertex2i& v1, 
    const Vertex2i& v2
) {
    int x = v1.pos.x;
    int y = v1.pos.y;

    int dx =  std::abs(v2.pos.x - v1.pos.x);
    int dy = -std::abs(v2.pos.y - v1.pos.y);

    int sx = v1.pos.x < v2.pos.x ? 1 : -1;
    int sy = v1.pos.y < v2.pos.y ? 1 : -1;

    int err = dx + dy;

    while (true) {
        Rasterizer::PutPixel(fb, {x, y}, v1.col);

        if (x == v2.pos.x && y == v2.pos.y) {
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

void Rasterizer::DrawLine(
    Framebuffer& fb, 
    const Line2i& l, 
    DrawLineMode m
) {
    Rasterizer::DrawLine(fb, l.s, l.e, m);

    return;
}

void Rasterizer::DrawLine(
    Framebuffer& fb, 
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

void Rasterizer::DrawTriangle(
    Framebuffer& fb, 
    const Triangle2i t
) {
    Vec2i min = Vec2i {
        std::min({ t.a.pos.x, t.b.pos.x, t.c.pos.x }),
        std::min({ t.a.pos.y, t.b.pos.y, t.c.pos.y })
    };

    Vec2i max = Vec2i {
        std::max({ t.a.pos.x, t.b.pos.x, t.c.pos.x }),
        std::max({ t.a.pos.y, t.b.pos.y, t.c.pos.y })
    };

    min.x = std::max(0, min.x);
    min.y = std::max(0, min.y);

    max.x = std::min(max.x, fb.width - 1);
    max.y = std::min(max.y, fb.height - 1);

    int area2 = Edge2i(t.a.pos, t.b.pos, t.c.pos);

    for (int y = min.y; y <= max.y; ++y) {
        for (int x = min.x; x <= max.x; ++x) {
            Vec2i p { x, y };

            int w0 = Edge2i(t.a.pos, t.b.pos, p);
            int w1 = Edge2i(t.b.pos, t.c.pos, p);
            int w2 = Edge2i(t.c.pos, t.a.pos, p);

            bool isInside =
                (w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0);
            
            if (!isInside) {
                continue;
            }
            
            float alpha = w0 / static_cast<float>(area2);
            float beta = w1 / static_cast<float>(area2);
            float gamma = w2 / static_cast<float>(area2);

            uint8_t r 
                = alpha * t.a.col.r 
                + beta * t.b.col.r 
                + gamma * t.c.col.r;

            uint8_t g
                = alpha * t.a.col.g 
                + beta * t.b.col.g 
                + gamma * t.c.col.g;
            uint8_t b 
                = alpha * t.a.col.b
                + beta * t.b.col.b
                + gamma * t.c.col.b;

            PutPixel(fb, p, { r, g, b });
        }
    }
}

};
