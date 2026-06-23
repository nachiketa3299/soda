#include <vector>
#include <cmath>

#include "Soda/Framebuffer.h"
#include "Soda/Rasterizer.h"
#include "Soda/Line.h"
#include "Soda/Vec.h"
#include "Soda/Color.h"
#include "Soda/MathUtils.h"
#include "Soda/Vertex.h"
#include "Soda/IO.h"

constexpr size_t WIDTH = 1024;
constexpr size_t HEIGHT = 1024;

using namespace Soda;

std::vector<Line2i> CreateRadialLines(FramebufferLegacy fb, Vec2i center, float radius, float step) {
    std::vector<Line2i> ret;

    int s = static_cast<int>(360.f / step);

    for (int i = 0; i < s; ++i) {

        int nx = center.x + static_cast<int>(std::round(radius * std::cos(DegreeToRadian(i * step))));
        int ny = center.y + static_cast<int>(std::round(radius * std::sin(DegreeToRadian(i * step))));

        nx = nx < 0 ? 0 : nx;
        nx = nx >= fb.width ? fb.width - 1 : nx;

        ny = ny < 0 ? 0 : ny;
        ny = ny >= fb.height ? fb.height - 1 : ny;

        float t = i / static_cast<float>(s);

        Rgb8 sc {
            LerpU8(0, 255, t),
            LerpU8(255, 0, t),
            LerpU8(0, 255, t),
        };

        Rgb8 ec {
            LerpU8(0, 255, 1.f - t),
            LerpU8(255, 0, 1.f - t),
            LerpU8(0, 255, 1.f - t),
        };

        ret.push_back(Line2i {
            Vertex2i { center, sc }, Vertex2i { Vec2i { nx, ny } , ec }
        });
    }

    return ret;
}

int main(void) {

    FramebufferLegacy fb(WIDTH, HEIGHT);

    const auto lines = CreateRadialLines(fb, {fb.width / 2, fb.height / 2}, (fb.width + fb.height) / 4.f, .5f / 10);

    LegacyRasterizer::Clear(fb, Rgb8::Black);

    for (const auto& l: lines) {
        LegacyRasterizer::DrawLine(fb, l, DrawLineMode::Naive);
    }

    WritePPM(fb, "naive.ppm");

    LegacyRasterizer::Clear(fb, Rgb8::Black);

    for (const auto& l: lines) {
        LegacyRasterizer::DrawLine(fb, l, DrawLineMode::Bresenham);
    }

    WritePPM(fb, "bresenham.ppm");

    return 0;
}
