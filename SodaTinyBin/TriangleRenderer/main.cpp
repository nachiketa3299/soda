#include "Soda.h"

#include <cstdio>

using namespace Soda;

constexpr int WIDTH = 32;
constexpr int HEIGHT = 32;

int main() {
    printf("Hello, Triangle!");
    Framebuffer fb(WIDTH, HEIGHT, Rgb8::Black);

    Vec2i a {static_cast<int>(0.5f * WIDTH), static_cast<int>(0.3f * HEIGHT)};  // 상단 중앙 (꼭대기)
    Vec2i b {static_cast<int>(0.3f * WIDTH), static_cast<int>(0.7f * HEIGHT)};  // 하단 왼쪽
    Vec2i c {static_cast<int>(0.7f * WIDTH), static_cast<int>(0.7f * HEIGHT)};  // 하단 오른쪽

    Vertex2i va { a, Rgb8::Red };
    Vertex2i vb { b, Rgb8::Green };
    Vertex2i vc { c, Rgb8::Blue };

    Rasterizer::DrawTriangle(fb, {va, vb, vc});

    WritePPM(fb, "triangle.ppm");
}