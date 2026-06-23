#include "Soda/Framebuffer.h"
#include "Soda/Rasterizer.h"
#include "Soda/Color.h"
#include "Soda/Vertex.h"
#include "Soda/IO.h"

#include <cmath>
#include <numbers>

using namespace Soda;

constexpr int WIDTH = 128;
constexpr int HEIGHT = 128;

int main() {
    Framebuffer fb { WIDTH, HEIGHT, Color4f::Black };
    Rasterizer rt { fb };

    const float pi = std::numbers::pi_v<float>;
    const float cx = WIDTH * 0.5f;
    const float cy = HEIGHT * 0.5f;
    const float radius = (WIDTH < HEIGHT ? WIDTH : HEIGHT) * 0.46f;
    const int count = 12;

    for (int i = 0; i < count; ++i) {
        float a0 = i * (2.f * pi / count);
        float a1 = (i + 2.f) * (2.f * pi / count);

        float hue = static_cast<float>(i) / count;
        Color4f col {
            0.5f + 0.5f * std::sin(hue * 2.f * pi),
            0.5f + 0.5f * std::sin(hue * 2.f * pi + 2.f * pi / 3.f),
            0.5f + 0.5f * std::sin(hue * 2.f * pi + 4.f * pi / 3.f),
            0.45f
        };

        Color4f tip {
            col.r, col.g, col.b, 0.85f
        };

        Vertex2f apex { { cx, cy }, tip };
        Vertex2f p0 { { cx + radius * std::cos(a0), cy + radius * std::sin(a0) }, col };
        Vertex2f p1 { { cx + radius * std::cos(a1), cy + radius * std::sin(a1) }, col };

        rt.FillTriangle({ apex, p0, p1 });
    }

    WritePPM(fb, "overlap.ppm");
    WriteBMP(fb, "overlap.bmp");
}
