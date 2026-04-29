#include <vector>
#include <cstdint>
#include <fstream>
#include <cstdio>

#define WIDTH 256
#define HEIGHT 256

#define OUT_FILE_NAME "output.ppm"

enum ColorIndex {
    R_IDX = 0, G_IDX, B_IDX, C_LEN
};

int main() {
    const size_t len = WIDTH * HEIGHT * C_LEN;

    std::vector<uint8_t> buff(len);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            const size_t idx = (y * WIDTH + x) * C_LEN;
            const uint8_t y_dir = (uint8_t)(((float)y / (HEIGHT - 1)) * 255.0f);
            const uint8_t x_dir = (uint8_t)(((float)x / (WIDTH - 1)) * 255.0f);

            buff[idx + R_IDX] = 255;
            buff[idx + G_IDX] = y_dir;
            buff[idx + B_IDX] = x_dir;

            std::printf("%d: (%d, %d) - (r:%d, g:%d, b:%d)\n", (int)idx, x, y, buff[idx + R_IDX], buff[idx + G_IDX], buff[idx + B_IDX]);
        }
    }

    std::ofstream out(OUT_FILE_NAME, std::ios::binary);

    /*
    P6
    3 3 255
    R G B
    R G B
    ...
    */

    out << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    out.write(reinterpret_cast<const char*>(buff.data()), buff.size());

    std::printf("saved %s", OUT_FILE_NAME);

    return 0;
}