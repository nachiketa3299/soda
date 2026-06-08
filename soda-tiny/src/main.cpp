#include "PPM/FrameBuffer3.h"
#include "PPM/Renderer3.h"

constexpr size_t WIDTH = 256;
constexpr size_t HEIGHT = 120;

using namespace SodaTiny::PPM;

int main(void) {

    FrameBuffer3 fb(WIDTH, HEIGHT);

    Renderer3::Clear(fb, Color8::red());
    Renderer3::DrawLine(fb, {10, 20}, {100, 200}, Color8::white(), DrawLineMode::Naive);

    File::SavePPM(fb, "test-green.ppm");

    return 0;
}

