#include "Soda/IO.h"

#include <fstream>
#include <cstdint>

namespace Soda {

void WritePPM(const Framebuffer& fb, const std::string& path) {
    std::ofstream out(path, std::ios::binary);

    out << "P6\n" << fb.Width() << " " << fb.Height() << "\n255\n";

    const Rgba8* px = fb.Data();
    const int count = fb.Width() * fb.Height();
    for (int i = 0; i < count; ++i) {
        const char rgb[3] = {
            static_cast<char>(px[i].r),
            static_cast<char>(px[i].g),
            static_cast<char>(px[i].b),
        };
        out.write(rgb, 3);
    }
}

void WriteBMP(const Framebuffer& fb, const std::string& path) {
    std::ofstream out(path, std::ios::binary);

    const int w = fb.Width();
    const int h = fb.Height();
    const int rowBytes = w * 3;
    const int pad = (4 - (rowBytes % 4)) % 4;
    const uint32_t imageSize = static_cast<uint32_t>((rowBytes + pad) * h);
    const uint32_t dataOffset = 14 + 40;
    const uint32_t fileSize = dataOffset + imageSize;

    auto u16 = [&out](uint16_t v) {
        out.put(static_cast<char>(v & 0xFF));
        out.put(static_cast<char>((v >> 8) & 0xFF));
    };
    auto u32 = [&out](uint32_t v) {
        out.put(static_cast<char>(v & 0xFF));
        out.put(static_cast<char>((v >> 8) & 0xFF));
        out.put(static_cast<char>((v >> 16) & 0xFF));
        out.put(static_cast<char>((v >> 24) & 0xFF));
    };

    out.put('B'); out.put('M');
    u32(fileSize);
    u16(0); u16(0);
    u32(dataOffset);

    u32(40);
    u32(static_cast<uint32_t>(w));
    u32(static_cast<uint32_t>(h));
    u16(1);
    u16(24);
    u32(0);
    u32(imageSize);
    u32(2835); u32(2835);
    u32(0); u32(0);

    const Rgba8* px = fb.Data();
    for (int y = h - 1; y >= 0; --y) {
        for (int x = 0; x < w; ++x) {
            const Rgba8& c = px[y * w + x];
            out.put(static_cast<char>(c.b));
            out.put(static_cast<char>(c.g));
            out.put(static_cast<char>(c.r));
        }
        for (int i = 0; i < pad; ++i) out.put(0);
    }
}

void WritePPM(FramebufferLegacy& fb, std::string name) {
    std::ofstream out(name, std::ios::binary);
    out << "P6\n" << fb.width << " " << fb.height << "\n255\n";
    out.write(reinterpret_cast<const char*>(fb.buff.data()), fb.buff.size());
}

}
