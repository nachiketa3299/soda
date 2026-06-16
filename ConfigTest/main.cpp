#include <cstdio>

int main() {
    printf("===[ConfigTest]===\n");

#if defined(__APPLE__)
    printf("- OS: macOS\n");
#elif defined(_WIN32)
    printf("- OS: Windows\n");
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
    printf("- Architecture: arm64\n");
#elif defined(__x86_64__) || defined(_M_X64)
    printf("- Architecture: x86_64\n");
#else
    printf("- Architecture: unknown\n");
#endif

#if defined(__clang__)
    printf("- Compiler: Clang %d.%d\n", __clang_major__, __clang_minor__);
#elif defined(_MSC_VER)
    printf("- Compiler: MSVC %d\n", _MSC_VER);
#endif

#if defined(NDEBUG)
    printf("- Build: Release\n");
#else
    printf("- Build: Debug\n");
#endif

    return 0;
}
