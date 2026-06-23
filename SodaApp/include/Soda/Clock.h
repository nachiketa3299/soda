#pragma once

#include <chrono>

namespace Soda {

class Clock {
public:
    void Update();
    float DeltaTime() const;

private:
    std::chrono::steady_clock::time_point last_ {
        std::chrono::steady_clock::now()
    };
    float dt_ = 0.f;
};

}