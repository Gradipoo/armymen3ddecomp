// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a250.hpp"

#include <cstdint>

namespace {

int loads = 0;

std::uint32_t load_word(std::uint32_t address) {
    ++loads;
    if (address != 0x1004u) return 0;
    return 0x55u;
}

am3d::exe::Call8007a250Block zero_block() {
    return am3d::exe::Call8007a250Block{0, 0, 0, 0, 0, 0};
}

}

int main() {
    loads = 0;
    am3d::exe::Call8007a250Block arrival = zero_block();
    const std::uint32_t arrival_result = am3d::exe::call_8007a250(arrival, 1u, load_word);
    if (loads != 0 || arrival_result != 0 || arrival.word0 != 2u || arrival.at14 != 0 ||
        arrival.at18 != 0 || arrival.at1c != 0) {
        return 1;
    }

    loads = 0;
    am3d::exe::Call8007a250Block linked = zero_block();
    linked.word0 = 0x10u;
    linked.link = 0x1000u;
    const std::uint32_t linked_result = am3d::exe::call_8007a250(linked, 1u, load_word);
    if (loads != 1 || linked_result != 0x55u || linked.word0 != 0x12u ||
        linked.at14 != 0x55u || linked.at18 != 0 || linked.at1c != 0x55u) {
        return 2;
    }

    loads = 0;
    am3d::exe::Call8007a250Block cleared = zero_block();
    cleared.word0 = 7u;
    cleared.word4 = 0x20u;
    cleared.link = 0x30u;
    const std::uint32_t cleared_result = am3d::exe::call_8007a250(cleared, 0u, load_word);
    if (loads != 0 || cleared_result != 0x30u || cleared.word0 != 5u ||
        cleared.at14 != 0x30u || cleared.at18 != 0x20u || cleared.at1c != 0x30u) {
        return 3;
    }
    return 0;
}
