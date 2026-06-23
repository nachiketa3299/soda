#include "Soda/Clock.h"

namespace Soda {

void Clock::Update() {
    auto now = std::chrono::steady_clock::now();
    dt_ = std::chrono::duration<float>(now - last_).count();
    last_ = now;
}

float Clock::DeltaTime() const {
    return dt_;
}

}