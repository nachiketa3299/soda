#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <cmath>

constexpr size_t WIDTH = 256;
constexpr size_t HEIGHT = 120;

enum class Channel : size_t {
    Red = 0, 
    Green, 
    Blue, 
    Len = 3
};

struct Pos2 {
    int x;
    int y;
};

struct Color8 {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static Color8 black() { return {0, 0, 0}; }
    static Color8 white() {return {255, 255, 255};}
    static Color8 red() {return{255, 0, 0};}
    static Color8 green() {return {0, 255, 0};}
    static Color8 blue() {return{0, 0, 255};}
};


enum class LineDrawMode {
    Naive
};

struct PPMFrameBuffer {
    PPMFrameBuffer(size_t w, size_t h)
        : width(w), height(h), 
          channel(static_cast<size_t>(Channel::Len)), 
          buff(width * height * channel) {
    }

    void clear(const Color8& c) {
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                update_pixel({(int)x, (int)y}, c);
            }
        }
    }

    void update_pixel(const Pos2& p, const Color8& c) {
        update_channel(p, Channel::Red, c.r);
        update_channel(p, Channel::Green, c.g);
        update_channel(p, Channel::Blue, c.b);
    }

    void update_channel(const Pos2& p, Channel ch, uint8_t v) {
        if (!(0 <= p.x && p.x < static_cast<int>(width) && 0 <= p.y && p.y < static_cast<int>(height))) {
            return;
        }

        size_t idx = (p.y * width + p.x) * channel + static_cast<size_t>(ch);

        if (idx >= buff.size()) {
            return;
        }

        buff[idx] = v;
    }

    void save_file(const std::string& fn) {
       std::ofstream out(fn, std::ios::binary);
       out << "P6\n" << width << " " << height << "\n255\n";
       out.write(reinterpret_cast<const char*>(buff.data()), buff.size());
    }

    void set_line_draw_mode(LineDrawMode new_mode) {
        lmode = new_mode;
    }

    void set_draw_color(const Color8& c) {
        dcolor = c;
    }

    void draw_line(const Pos2& s, const Pos2& e) {
        switch (lmode) {
            default:
            case LineDrawMode::Naive: draw_line_naive(s, e, dcolor); break;
        }
    }

private:
    void draw_line_naive(const Pos2& s, const Pos2& e, const Color8& c) {
        if (e.x == s.x) {
            for (int y = s.y; y <= e.y; ++y) {
                update_pixel({s.x, y}, c);
            }
            return;
        }

        Pos2 l, r;

        if (s.x < e.x) {
            l = s;
            r = e;
        } else {
            l = e;
            r = s;
        }

        float dx = static_cast<float>(r.x - l.x);
        float dy = static_cast<float>(r.y - l.y);
        float a = dy / dx;

        if (std::abs(dx) >= std::abs(dy)) {
            for (int x = l.x; x <= r.x; ++x) {
                int ty = l.y + static_cast<int>(std::floor(a * (x - l.x)));
                update_pixel({x, ty}, c);
            }
        } else {
            for (int y = l.y; y <= r.y; ++y) {
                int tx = l.x + static_cast<int>(std::floor(a * (y - l.y)));
                update_pixel({tx, y}, c);
            }
        }

    }

public:
    const size_t width;
    const size_t height;
    const size_t channel;

    LineDrawMode lmode = LineDrawMode::Naive;
    Color8 dcolor = Color8::black();

    std::vector<uint8_t> buff;
};

int main(void) {
    PPMFrameBuffer fb(WIDTH, HEIGHT);

    fb.clear(Color8::black());
    fb.set_line_draw_mode(LineDrawMode::Naive);
    fb.set_draw_color(Color8::white());

    // 일반
    fb.draw_line({10, 10}, {300, 100});
    // 역방향
    fb.draw_line({180, 180}, {20, 20});
    // 수직선
    fb.draw_line({150, 0}, {150, 100});
    // 완만한 경사
    fb.draw_line({0, 0}, {256, 5});
    // 급격한 경사
    fb.draw_line({0, 0}, {5, 100});

    fb.save_file("line.ppm");

    return 0;
}
