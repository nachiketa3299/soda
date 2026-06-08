#include "PPM/Renderer3.h"

#include <cmath>
#include <fstream>

namespace SodaTiny::PPM {

void Renderer3::PutPixel(FrameBuffer3& fb, const Pos2& p, const Color8& c) {
    size_t idx = 3 * (p.x + fb.width * p.y);

    fb.buff[idx + 0] = c.r;
    fb.buff[idx + 1] = c.g;
    fb.buff[idx + 2] = c.b;
}

void Renderer3::Clear(FrameBuffer3& fb, const Color8& c) {
    for (int h = 0; h < fb.height; ++h) {
        for (int w = 0; w < fb.width; ++w) {
            PutPixel(fb, {w, h}, c);
        }
    }
}

void drawLineNaive(FrameBuffer3& fb, const Pos2& p1, const Pos2& p2, const Color8& c) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;

    int step = std::max(std::abs(dx), std::abs(dy));

    for (int i = 0; i < step; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(step);

        float x = p1.x + dx * t;
        float y = p1.y + dy * t;

        int nx = static_cast<int>(std::floor(x));
        int ny = static_cast<int>(std::floor(y));

        Renderer3::PutPixel(fb, {nx, ny}, c);
    }
}

void Renderer3::DrawLine(FrameBuffer3& fb, const Pos2& p1, const Pos2& p2, const Color8& c, DrawLineMode m) {
    switch (m) {
        default:
        case DrawLineMode::Naive: drawLineNaive(fb, p1, p2, c); break;
    }
    return;
}


void File::SavePPM(FrameBuffer3& fb, std::string name) {
    std::ofstream out(name, std::ios::binary);

    out << "P6\n" << fb.width << " " << fb.height << "\n255\n";
    out.write(reinterpret_cast<const char*>(fb.buff.data()), fb.buff.size());
}

};