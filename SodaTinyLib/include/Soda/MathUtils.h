#pragma once

#include "Soda/Color.h"
#include "Vec.h"

namespace Soda {

float DegreeToRadian(float degree);

int Edge2i(const Vec2i& a, const Vec2i& b, const Vec2i& p);

uint8_t LerpU8(int s, int e, float t);

Rgb8 LerpRgb8(Rgb8 s, Rgb8 e, float t);
Rgba8 LerpRgba8(Rgba8 s, Rgba8 e, float t);

}