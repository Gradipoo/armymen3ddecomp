// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include <SDL.h>
#include <array>
#include <stdexcept>
#include <thread>

namespace am3d::platform {
namespace {
std::runtime_error error(const char* operation) {
    return std::runtime_error(std::string(operation) + ": " + SDL_GetError());
}
}

struct SdlPlatform::Impl {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_GameController* controller = nullptr;
    unsigned texture_width = 0;
    unsigned texture_height = 0;
    std::vector<std::uint32_t> pixels;
    std::chrono::steady_clock::time_point deadline = std::chrono::steady_clock::now();
    bool initialized = false;
    bool paced = false;
    exe::DisplayEnvironment display{};
    exe::DrawEnvironment drawing{};
    bool have_display = false;

    ~Impl() {
        if (controller) SDL_GameControllerClose(controller);
        if (texture) SDL_DestroyTexture(texture);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        if (initialized) SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    }

    void open_controller() {
        if (controller && !SDL_GameControllerGetAttached(controller)) {
            SDL_GameControllerClose(controller);
            controller = nullptr;
        }
        if (controller) return;
        for (int i = 0; i < SDL_NumJoysticks(); ++i) {
            if (SDL_IsGameController(i)) {
                controller = SDL_GameControllerOpen(i);
                if (controller) break;
            }
        }
    }

    void draw_view(int width, int height) const {
        if (!texture || width <= 0 || height <= 0) throw std::runtime_error("no display frame available");
        SDL_Rect destination{0, 0, width, height};
        if (width * 3 > height * 4) {
            destination.w = height * 4 / 3;
            destination.x = (width - destination.w) / 2;
        } else {
            destination.h = width * 3 / 4;
            destination.y = (height - destination.h) / 2;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (SDL_RenderClear(renderer) != 0 || SDL_RenderCopy(renderer, texture, nullptr, &destination) != 0)
            throw error("render view");
    }
};

SdlPlatform::SdlPlatform(const char* title, int width, int height, bool hidden)
    : impl_(std::make_unique<Impl>()) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("invalid window size");
    SDL_SetMainReady();
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) throw error("SDL init");
    impl_->initialized = true;
    impl_->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_RESIZABLE | (hidden ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN));
    if (!impl_->window) throw error("create window");
    impl_->renderer = SDL_CreateRenderer(impl_->window, -1, SDL_RENDERER_ACCELERATED);
    if (!impl_->renderer) impl_->renderer = SDL_CreateRenderer(impl_->window, -1, SDL_RENDERER_SOFTWARE);
    if (!impl_->renderer) throw error("create renderer");
    impl_->open_controller();
}

SdlPlatform::~SdlPlatform() = default;

void SdlPlatform::apply_display(const exe::DisplayEnvironment& environment) {
    impl_->display = environment;
    impl_->have_display = true;
}

void SdlPlatform::apply_draw(const exe::DrawEnvironment& environment) {
    impl_->drawing = environment;
}

const exe::DrawEnvironment& SdlPlatform::drawing_environment() const {
    return impl_->drawing;
}

void SdlPlatform::present(const FillVram& vram) {
    if (!impl_->have_display) throw std::runtime_error("display environment not set");
    if (impl_->display.interlaced) throw std::invalid_argument("interlaced display is not implemented");
    if (impl_->display.rgb24) throw std::invalid_argument("24-bit display is not implemented");
    present(vram, impl_->display.x & 1023, impl_->display.y & 511,
        impl_->display.width, impl_->display.height);
}

PadState SdlPlatform::poll() {
    PadState state;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(impl_->window))) state.quit = true;
    }
    impl_->open_controller();
    SDL_GameControllerUpdate();
    if (!impl_->controller) return state;
    const std::array<SDL_GameControllerButton, 16> mapping{
        SDL_CONTROLLER_BUTTON_BACK, SDL_CONTROLLER_BUTTON_LEFTSTICK, SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        SDL_CONTROLLER_BUTTON_START, SDL_CONTROLLER_BUTTON_DPAD_UP, SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        SDL_CONTROLLER_BUTTON_INVALID, SDL_CONTROLLER_BUTTON_INVALID,
        SDL_CONTROLLER_BUTTON_LEFTSHOULDER, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        SDL_CONTROLLER_BUTTON_Y, SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_X,
    };
    for (unsigned bit = 0; bit < mapping.size(); ++bit) {
        if (mapping[bit] != SDL_CONTROLLER_BUTTON_INVALID &&
            SDL_GameControllerGetButton(impl_->controller, mapping[bit])) {
            state.buttons &= static_cast<std::uint16_t>(~(1u << bit));
        }
    }
    if (SDL_GameControllerGetAxis(impl_->controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 8192)
        state.buttons &= static_cast<std::uint16_t>(~(1u << 8));
    if (SDL_GameControllerGetAxis(impl_->controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 8192)
        state.buttons &= static_cast<std::uint16_t>(~(1u << 9));
    return state;
}

void SdlPlatform::present(const FillVram& vram, unsigned x, unsigned y, unsigned width, unsigned height) {
    if (!width || !height || width > FillVram::width || height > FillVram::height ||
        x >= FillVram::width || y >= FillVram::height) throw std::invalid_argument("invalid display view");
    if (width != impl_->texture_width || height != impl_->texture_height) {
        if (impl_->texture) SDL_DestroyTexture(impl_->texture);
        impl_->texture = SDL_CreateTexture(impl_->renderer, SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING, static_cast<int>(width), static_cast<int>(height));
        if (!impl_->texture) throw error("create texture");
        impl_->texture_width = width;
        impl_->texture_height = height;
        impl_->pixels.resize(width * height);
    }
    for (unsigned row = 0; row < height; ++row) {
        for (unsigned col = 0; col < width; ++col) {
            impl_->pixels[row * width + col] = vram.argb((x + col) & 1023, (y + row) & 511);
        }
    }
    if (SDL_UpdateTexture(impl_->texture, nullptr, impl_->pixels.data(), width * 4) != 0)
        throw error("update texture");
    int output_width = 0, output_height = 0;
    if (SDL_GetRendererOutputSize(impl_->renderer, &output_width, &output_height) != 0)
        throw error("renderer output size");
    if (output_width <= 0 || output_height <= 0) return;
    impl_->draw_view(output_width, output_height);
    SDL_RenderPresent(impl_->renderer);
}

void SdlPlatform::wait_next_frame(std::chrono::nanoseconds period) {
    if (period.count() <= 0) throw std::invalid_argument("frame period must be positive");
    const auto now = std::chrono::steady_clock::now();
    if (!impl_->paced || impl_->deadline < now - period * 4) impl_->deadline = now;
    impl_->paced = true;
    impl_->deadline += period;
    std::this_thread::sleep_until(impl_->deadline);
}

std::vector<std::uint32_t> SdlPlatform::readback(int& width, int& height) const {
    if (SDL_GetRendererOutputSize(impl_->renderer, &width, &height) != 0) throw error("readback size");
    // Present invalidates the back buffer on some renderers. Redraw before reading.
    impl_->draw_view(width, height);
    std::vector<std::uint32_t> pixels(static_cast<std::size_t>(width) * height);
    if (SDL_RenderReadPixels(impl_->renderer, nullptr, SDL_PIXELFORMAT_ARGB8888,
        pixels.data(), width * 4) != 0) throw error("read frame");
    return pixels;
}

void SdlPlatform::save_frame(const std::string& path) const {
    int width, height;
    auto pixels = readback(width, height);
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.data(), width, height,
        32, width * 4, SDL_PIXELFORMAT_ARGB8888);
    if (!surface) throw error("capture surface");
    const int result = SDL_SaveBMP(surface, path.c_str());
    SDL_FreeSurface(surface);
    if (result != 0) throw error("save frame");
}

}
