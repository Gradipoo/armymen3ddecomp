// SPDX-License-Identifier: GPL-3.0-or-later
#include "disc_front_tim_load.hpp"
#include "prototype_task_7_menu.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace {

constexpr int kSkipNoDisc = 77;

std::filesystem::path resolve_disc_root() {
    if (std::filesystem::is_directory("build/disc")) {
        return "build/disc";
    }
    if (std::filesystem::is_directory("disc")) {
        return "disc";
    }
    return {};
}

}  // namespace

// Same transition as the disc-free checkpoint, with owner FRONT bytes present.
int main() {
    const std::vector<std::uint8_t> front_bytes =
        am3d::platform::load_front_tim_disc_bytes(resolve_disc_root());
    if (front_bytes.empty()) {
        return kSkipNoDisc;
    }

    const am3d::exe::PrototypeTask7MenuResult menu = am3d::exe::run_prototype_task_7_menu_transition(
        am3d::exe::prototype_task_7_pad_get_state, front_bytes.data(), front_bytes.size());
    if (menu.s7_after_a != 8u || menu.s7_after_b != 9u || !menu.has_front) {
        return 1;
    }
    if (menu.tail_0b != 0u || menu.tail_87 != 0x80u) {
        return 2;
    }
    if (!menu.destination_stated || menu.destination != 0x80064f14u ||
        menu.word_address != 0x800c3ea4u) {
        return 3;
    }
    return 0;
}
