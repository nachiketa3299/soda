#pragma once

#include "Soda/Framebuffer.h"
#include <string>

namespace Soda {

void WritePPM(const Framebuffer& fb, const std::string& path);
void WriteBMP(const Framebuffer& fb, const std::string& path);

// legacy (LineRenderer가 아직 사용)
void WritePPM(FramebufferLegacy& fb, std::string name);

}
