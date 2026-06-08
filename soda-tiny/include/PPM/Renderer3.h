#pragma once

#include "PPM/FrameBuffer3.h"

#include <string>

namespace SodaTiny::PPM {

struct Pos2 {
    int x;
    int y;
};

enum class DrawLineMode {
    Naive
};

struct Renderer3 {

static void PutPixel(FrameBuffer3& fb, const Pos2& p, const Color8& c);

static void Clear(FrameBuffer3& fb, const Color8& c);

static void DrawLine(FrameBuffer3& fb, const Pos2& p1, const Pos2& p2, const Color8& c, DrawLineMode m);

};

struct File {

static void SavePPM(FrameBuffer3& fb, std::string name);

};

}