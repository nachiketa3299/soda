#include "Soda/MathUtils.h"

#include <numbers>

namespace Soda {

float DegreeToRadian(float degree) {
    return degree * std::numbers::pi_v<float> / 180.f;
}

int Edge2i(const Vec2i& a, const Vec2i& b, const Vec2i& p) {
    Vec2i ab = b - a;
    Vec2i ap = p - a;

    return Vec2i::Cross(ab, ap);
}

uint8_t LerpU8(int s, int e, float t) {
    return static_cast<uint8_t>(s + (e - s) * t);
}

Rgb8 LerpRgb8(Rgb8 s, Rgb8 e, float t) {
    return Rgb8 {
        LerpU8(s.r, e.r, t),
        LerpU8(s.g, e.g, t),
        LerpU8(s.b, e.b, t)
    };
}

Rgba8 LerpRgba8(Rgba8 s, Rgba8 e, float t) {
    return Rgba8 {
        LerpU8(s.r, e.r, t),
        LerpU8(s.g, e.g, t),
        LerpU8(s.b, e.b, t),
        LerpU8(s.a, e.a, t)
    };
}

}