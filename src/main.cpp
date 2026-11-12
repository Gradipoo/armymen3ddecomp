// SPDX-License-Identifier: GPL-3.0-or-later
#include "browser.hpp"
#include "keyboard.hpp"
#include "load.hpp"
#include "overlay.hpp"

int main() {
    (void)am3d::exe::load_status();
    (void)am3d::input::keyboard_status();
    (void)am3d::net::browser_status();
    (void)am3d::mods::overlay_status();
    return 0;
}
