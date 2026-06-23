#include "Soda/Mesh.h"
#include "Soda/Window.h"
#include "Soda/Rasterizer.h"
#include "Soda/Color.h"
#include "Soda/Framebuffer.h"
#include "Soda/App.h"
#include "Soda/MathUtils.h"
#include "Soda/Vec.h"

#include <cmath>
#include <numbers>

using namespace Soda;

constexpr int WIDTH = 512;
constexpr int HEIGHT = 512;

int main() {
    App app { "Cube", WIDTH, HEIGHT };

    const Mesh cube = Mesh::TestCube;
    Vec3f axis = { 1.f, 1.f, 0.f };

    float deg = 0.f;   // 누적 각도(도)
    float t   = 0.f;   // 누적 시간(초)

    const float baseSpeed = 30.f;   // 기본 회전속도 (deg/s)
    const float amplitude = 25.f;   // 속도 진폭 (deg/s) — base보다 작아야 항상 전진
    const float period    = 2.f;    // 진동 주기 (초)

    const float pi = std::numbers::pi_v<float>;

    auto tick = [&](float dt, Rasterizer& rt) {
        t += dt;
        float omega = baseSpeed + amplitude * std::sin(2.f * pi * t / period);  // 항상 양수
        deg += omega * dt;                                                      // 적분
        auto mvp = Mat4f::Rotation(axis, DegreeToRadian(deg));
        rt.DrawMesh(cube, mvp);
    };

    app.Run(tick);

    return 0;
}