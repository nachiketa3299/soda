#pragma once

#include "Soda/Color.h"
#include "Soda/Vec.h"

namespace Soda {

float DegreeToRadian(float degree);

int Edgei(const Vec2i& a, const Vec2i& b, const Vec2i& p);
float Edgef(const Vec2f& a, const Vec2f& b, const Vec2f& p);

float Lerp(float src, float dst, float t);
uint8_t LerpU8(int s, int e, float t);

Rgb8 LerpRgb8(Rgb8 s, Rgb8 e, float t);
Rgba8 LerpRgba8(Rgba8 s, Rgba8 e, float t);

}