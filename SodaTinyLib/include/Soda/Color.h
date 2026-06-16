#pragma once

#include <cstdint>

namespace Soda {

struct Rgb8 {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static const Rgb8 Black;
    static const Rgb8 White;
    static const Rgb8 Red;
    static const Rgb8 Green;
    static const Rgb8 Blue;
};

inline const Rgb8 Rgb8::Black { 0  ,   0,   0 };
inline const Rgb8 Rgb8::White { 255, 255, 255 };
inline const Rgb8 Rgb8::Red   { 255,   0,   0 };
inline const Rgb8 Rgb8::Green { 0  , 255,   0 };
inline const Rgb8 Rgb8::Blue  { 0  ,   0, 255 };

struct Rgba8 {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

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


}