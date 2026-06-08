#pragma once

#include <vector>
#include <cstdint>

namespace SodaTiny::PPM {

struct Color8 {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static Color8 black() { return {0, 0, 0}; }
    static Color8 white() {return {255, 255, 255};}
    static Color8 red() {return{255, 0, 0};}
    static Color8 green() {return {0, 255, 0};}
    static Color8 blue() {return{0, 0, 255};}
};

enum class FB3Channel {
    Red = 0,
    Green = 1,
    Blue = 2,
};

struct FrameBuffer3 {
    FrameBuffer3(size_t w, size_t h);
    FrameBuffer3(size_t w, size_t h, const Color8& c);

    const size_t width;
    const size_t height;
    const size_t channel = 3;

    std::vector<uint8_t> buff;
};

};