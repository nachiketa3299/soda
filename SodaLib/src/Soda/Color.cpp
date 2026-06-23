#include "Soda/Color.h"
#include "Soda/MathUtils.h"

#include <cmath>
#include <algorithm>

namespace Soda {

Color4f& Color4f::operator+=(const Color4f &oth) {
    r += oth.r;
    g += oth.g;
    b += oth.b;
    a += oth.a;

    return *this;
}

Color4f& Color4f::operator-=(const Color4f &oth) {
    r -= oth.r;
    g -= oth.g;
    b -= oth.b;
    a -= oth.a;

    return *this;
}

Color4f& Color4f::operator*=(float c) {
    r *= c;
    g *= c;
    b *= c;
    a *= c;

    return *this;
}

Color4f& Color4f::operator/=(float c) {
    r /= c;
    g /= c;
    b /= c;
    a /= c;

    return *this;
}

Color4f Lerp(const Color4f& a, const Color4f& b, float t) {
    return Color4f {
        Lerp(a.r, b.r, t),
        Lerp(a.g, b.g, t),
        Lerp(a.b, b.b, t),
        Lerp(a.a, b.a, t),
    };
}

Color4f ToColor4f(const Rgba8& t) {
    return Color4f { 
        t.r / 255.f, 
        t.g / 255.f,
        t.b / 255.f,
        t.a / 255.f
    };
}

Rgba8 ToRgba8(const Color4f& t) {
    return Rgba8 { 
        static_cast<uint8_t>(std::round(255.f * std::clamp(t.r, 0.f, 1.f))),
        static_cast<uint8_t>(std::round(255.f * std::clamp(t.g, 0.f, 1.f))),
        static_cast<uint8_t>(std::round(255.f * std::clamp(t.b, 0.f, 1.f))),
        static_cast<uint8_t>(std::round(255.f * std::clamp(t.a, 0.f, 1.f)))
    };
}

}