#include "Soda/Window.h"

#include <SDL3/SDL.h>
#include <string>

namespace Soda {

struct Window::Impl {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    int width = 0;
    int height = 0;
    bool shouldClose = false;
};

Window::Window(std::string_view title, int width, int height) 
    : impl_(std::make_unique<Impl>())
{
    impl_->width = width;
    impl_->height = height;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init 실패: %s", SDL_GetError());
    };

    impl_->window = SDL_CreateWindow(
        std::string(title).c_str(), width, height, 0
    );

    impl_->renderer = SDL_CreateRenderer(impl_->window, nullptr);

    impl_->texture = SDL_CreateTexture(
        impl_->renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
    );
}

Window::~Window() {
    if (impl_->texture) {
        SDL_DestroyTexture(impl_->texture);
    }

    if (impl_->renderer) {
        SDL_DestroyRenderer(impl_->renderer);
    }

    if (impl_->window) {
        SDL_DestroyWindow(impl_->window);
    }

    SDL_Quit();
}

void Window::PollEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            impl_->shouldClose = true;
        }
    }
}

bool Window::ShouldClose() const {
    return impl_->shouldClose;
}

void Window::Present(const Framebuffer& fb) {
    SDL_UpdateTexture(impl_->texture, nullptr, fb.Data(), fb.Width() * static_cast<int>(sizeof(Rgba8)));
    SDL_RenderClear(impl_->renderer);
    SDL_RenderTexture(impl_->renderer, impl_->texture, nullptr, nullptr);
    SDL_RenderPresent(impl_->renderer);
}

}