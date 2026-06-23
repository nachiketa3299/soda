#pragma once

#include <cstdint>

namespace Soda {

struct Rgb8 {
    uint8_t r, g, b;

    static const Rgb8 Black;
    static const Rgb8 White;
    static const Rgb8 Red;
    static const Rgb8 Green;
    static const Rgb8 Blue;
};

inline const Rgb8 Rgb8::Black {   0,   0,   0 };
inline const Rgb8 Rgb8::White { 255, 255, 255 };
inline const Rgb8 Rgb8::Red   { 255,   0,   0 };
inline const Rgb8 Rgb8::Green {   0, 255,   0 };
inline const Rgb8 Rgb8::Blue  {   0,   0, 255 };

struct Rgba8 {
    uint8_t r, g, b, a;

    static const Rgba8 Black;
    static const Rgba8 White;
    static const Rgba8 Red;
    static const Rgba8 Green;
    static const Rgba8 Blue;
};

inline const Rgba8 Rgba8::Black {   0,   0,   0, 255 };
inline const Rgba8 Rgba8::White { 255, 255, 255, 255 };
inline const Rgba8 Rgba8::Red   { 255,   0,   0, 255 };
inline const Rgba8 Rgba8::Green {   0, 255,   0, 255 };
inline const Rgba8 Rgba8::Blue  {   0,   0, 255, 255 };

struct Color4f {
    float r, g, b, a;

    Color4f& operator+=(const Color4f& oth);
    Color4f& operator-=(const Color4f& oth);
    Color4f& operator*=(float c);
    Color4f& operator/=(float c);

    static const Color4f Black;
    static const Color4f White;
    static const Color4f Red;
    static const Color4f Green;
    static const Color4f Blue;
    static const Color4f Yellow;
    static const Color4f Cyan;
    static const Color4f Magenta;
    static const Color4f Orange;
    static const Color4f Gray;
};

inline constexpr Color4f Color4f::Black   { 0.f, 0.f, 0.f, 1.f };
inline constexpr Color4f Color4f::White   { 1.f, 1.f, 1.f, 1.f };
inline constexpr Color4f Color4f::Red     { 1.f, 0.f, 0.f, 1.f };
inline constexpr Color4f Color4f::Green   { 0.f, 1.f, 0.f, 1.f };
inline constexpr Color4f Color4f::Blue    { 0.f, 0.f, 1.f, 1.f };
inline constexpr Color4f Color4f::Yellow  { 1.f, 1.f, 0.f, 1.f };
inline constexpr Color4f Color4f::Cyan    { 0.f, 1.f, 1.f, 1.f };
inline constexpr Color4f Color4f::Magenta { 1.f, 0.f, 1.f, 1.f };
inline constexpr Color4f Color4f::Orange  { 1.f, 0.5f, 0.f, 1.f };
inline constexpr Color4f Color4f::Gray    { 0.5f, 0.5f, 0.5f, 1.f };

inline Color4f operator+(Color4f l, const Color4f& r) { return l += r; }
inline Color4f operator-(Color4f l, const Color4f& r) { return l -= r; }
inline Color4f operator*(Color4f l, float r) { return l *= r; }
inline Color4f operator*(float l, Color4f r) { return r *= l; }
inline Color4f operator/(Color4f l, float r) { return l /= r; }

Color4f Lerp(const Color4f& a, const Color4f& b, float t);

Color4f ToColor4f(const Rgba8& t);
Rgba8 ToRgba8(const Color4f& t);

}