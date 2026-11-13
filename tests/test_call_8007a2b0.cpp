// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a2b0.hpp"

#include <cstdint>

namespace {

int loads = 0;

std::uint32_t load_word(std::uint32_t address) {
    ++loads;
    switch (address) {
    case 0x2000u: return 0x11u;
    case 0x2004u: return 0x99u;
    case 0x2008u: return 0x77u;
    case 0x1004u: return 0x2000u;
    case 0x4004u: return 0x5000u;
    case 0x5004u: return 0x6000u;
    case 0x6000u: return 0x44u;
    default: return 0;
    }
}

am3d::exe::Call8007a2b0Block arrival_block() {
    return am3d::exe::Call8007a2b0Block{2u, 0, 0, 0, 0};
}

}

int main() {
    loads = 0;
    std::uint32_t slot = 0xabcdefu;
    am3d::exe::Call8007a2b0Block arrival = arrival_block();
    const std::uint32_t arrival_result = am3d::exe::call_8007a2b0(arrival, &slot, load_word);
    if (loads != 0 || arrival_result != 0 || slot != 0 || arrival.word0 != 2u ||
        arrival.at14 != 0 || arrival.at18 != 1u || arrival.at1c != 0) {
        return 1;
    }

    slot = 1u;
    am3d::exe::Call8007a2b0Block frozen = arrival_block();
    frozen.at18 = 0xffffffffu;
    if (am3d::exe::call_8007a2b0(frozen, &slot, load_word) != 0 || frozen.at18 != 0xffffffffu ||
        slot != 0) {
        return 2;
    }

    slot = 1u;
    am3d::exe::Call8007a2b0Block cleared = arrival_block();
    cleared.word0 = 0;
    cleared.at18 = 5u;
    if (am3d::exe::call_8007a2b0(cleared, &slot, load_word) != 0 || cleared.at18 != 4u) {
        return 3;
    }

    loads = 0;
    slot = 0;
    am3d::exe::Call8007a2b0Block linked = arrival_block();
    linked.link = 0x1000u;
    linked.at1c = 0x2000u;
    const std::uint32_t linked_result = am3d::exe::call_8007a2b0(linked, &slot, load_word);
    if (loads != 2 || linked_result != 1u || slot != 0x11u || linked.at14 != 0x2000u ||
        linked.at18 != 1u || linked.at1c != 0x99u) {
        return 4;
    }

    loads = 0;
    slot = 0;
    am3d::exe::Call8007a2b0Block same = arrival_block();
    same.link = 0x2000u;
    same.at1c = 0x2000u;
    if (am3d::exe::call_8007a2b0(same, &slot, load_word) != 1u || slot != 0x11u ||
        same.at1c != 0) {
        return 5;
    }

    loads = 0;
    slot = 0;
    am3d::exe::Call8007a2b0Block bit0 = arrival_block();
    bit0.word0 = 1u;
    bit0.link = 0x3000u;
    bit0.at1c = 0x2000u;
    bit0.at18 = 4u;
    if (am3d::exe::call_8007a2b0(bit0, &slot, load_word) != 1u || slot != 0x11u ||
        bit0.at18 != 3u || bit0.at1c != 0x77u) {
        return 6;
    }

    loads = 0;
    slot = 0;
    am3d::exe::Call8007a2b0Block walked = arrival_block();
    walked.word0 = 0;
    walked.link = 0x4000u;
    walked.at1c = 0x6000u;
    walked.at18 = 8u;
    if (am3d::exe::call_8007a2b0(walked, &slot, load_word) != 1u || slot != 0x44u ||
        walked.at18 != 7u || walked.at1c != 0x5000u) {
        return 7;
    }
    return 0;
}
