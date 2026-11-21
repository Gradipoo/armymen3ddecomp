// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e40.hpp"

#include <cstdint>

namespace {

std::uint32_t g_port = 0xffffffffu;
std::uint32_t g_state = 0u;

std::uint32_t pad_get_state(std::uint32_t port) {
    g_port = port;
    return g_state;
}

}

int main() {
    am3d::exe::MenuLoopHead head{};
    head.s6 = 9u;
    g_state = 2u;
    am3d::exe::call_80064e40(1u, 2u, pad_get_state, head);
    if (g_port != 0x12u || head.s3 != 0x12u) {
        return 1;
    }
    if (head.s6 != 0u || head.s2 != 2u || head.below_seven != 1u ||
        !head.entered_64e68 || head.branch_to_64f14 ||
        head.branch_delay_v0 != 0x800c0000u) {
        return 2;
    }
    g_state = 7u;
    am3d::exe::call_80064e40(0u, 0u, pad_get_state, head);
    if (g_port != 0u || head.s2 != 7u || head.below_seven != 0u ||
        !head.branch_to_64f14 || head.entered_64e68 ||
        head.branch_delay_v0 != 0x800c0000u) {
        return 3;
    }
    return 0;
}
