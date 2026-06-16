#include "Soda/PPM.h"

#include <fstream>

namespace Soda {

void WritePPM(Framebuffer& fb, std::string name) {
    std::ofstream out(name, std::ios::binary);

    out << "P6\n" << fb.width << " " << fb.height << "\n255\n";
    out.write(reinterpret_cast<const char*>(fb.buff.data()), fb.buff.size());
}

}