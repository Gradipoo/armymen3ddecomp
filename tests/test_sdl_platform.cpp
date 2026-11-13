// SPDX-License-Identifier: GPL-3.0-or-later
#include "sdl_platform.hpp"
#include "display_clear.hpp"
#include <SDL.h>
#include <iostream>
#include <stdexcept>

using namespace am3d;

int main() {
    try {
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
        platform::SdlPlatform host("Platform integration test", 128, 128, true);
        platform::FillVram vram;
        exe::fill_display(0x0000ffu, {0, 0, 0, 0, 512, 240}, vram);
        host.present(vram, 0, 0, 512, 240);
        int width = 0, height = 0;
        const auto pixels = host.readback(width, height);
        if (width != 128 || height != 128 || pixels[64 * width + 64] != 0xffff0000u ||
            pixels[0] != 0xff000000u) return 1;

        // The selected page is displayed while the next page becomes the draw target.
        exe::fill_display(0x00ff00u, {0, 256, 0, 0, 512, 240}, vram);
        exe::DisplayBufferState buffers;
        buffers.buffers = {{1, 0, 0}, {std::nullopt, 0, 256}};
        buffers.width = buffers.right = 512;
        buffers.height = buffers.bottom = 240;
        buffers.mode = 2;
        buffers.buffer_count = 2;
        exe::clear_display_buffers(0, buffers, host, vram);
        if (vram.pixel(0, 0) != 0 || vram.pixel(0, 256) != 0 || buffers.drawing != 0) return 8;
        exe::fill_display(0x0000ffu, {0, 0, 0, 0, 512, 240}, vram);
        exe::fill_display(0x00ff00u, {0, 256, 0, 0, 512, 240}, vram);
        exe::advance_display_buffers(buffers, host);
        host.present(vram);
        if (host.readback(width, height)[64 * width + 64] != 0xffff0000u ||
            host.drawing_environment().y != 256) return 6;
        exe::advance_display_buffers(buffers, host);
        host.present(vram);
        if (host.readback(width, height)[64 * width + 64] != 0xff00ff00u ||
            host.drawing_environment().y != 0) return 7;

        const int device = SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,
            SDL_CONTROLLER_AXIS_MAX, SDL_CONTROLLER_BUTTON_MAX, 0);
        if (device < 0) throw std::runtime_error(SDL_GetError());
        SDL_Joystick* joystick = SDL_JoystickOpen(device);
        if (!joystick) throw std::runtime_error(SDL_GetError());
        SDL_JoystickSetVirtualAxis(joystick, SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768);
        SDL_JoystickSetVirtualAxis(joystick, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, -32768);
        host.poll();
        SDL_JoystickSetVirtualButton(joystick, SDL_CONTROLLER_BUTTON_A, 1);
        SDL_JoystickSetVirtualButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 1);
        SDL_JoystickSetVirtualAxis(joystick, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 32767);
        const auto held = host.poll();
        if ((held.buttons & (1u << 14)) || (held.buttons & (1u << 5)) ||
            (held.buttons & (1u << 8))) return 2;
        SDL_JoystickSetVirtualButton(joystick, SDL_CONTROLLER_BUTTON_A, 0);
        SDL_JoystickSetVirtualButton(joystick, SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 0);
        SDL_JoystickSetVirtualAxis(joystick, SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768);
        if (host.poll().buttons != 0xffff) return 3;
        SDL_JoystickClose(joystick);
        SDL_JoystickDetachVirtual(device);
        if (host.poll().buttons != 0xffff) return 4;

        host.wait_next_frame(std::chrono::milliseconds(1));
        SDL_Event quit{};
        quit.type = SDL_QUIT;
        if (SDL_PushEvent(&quit) != 1 || !host.poll().quit) return 5;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 10;
    }
}
