// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a3b0.hpp"

#include <cstdint>

namespace {

int calls = 0;
std::uint32_t got_a0 = 0;
std::uint32_t* got_slot = nullptr;
std::uint32_t got_a2 = 0;
std::uint32_t got_a3 = 0;

void record(std::uint32_t a0, std::uint32_t* slot10, std::uint32_t a2, std::uint32_t a3) {
    ++calls;
    got_a0 = a0;
    got_slot = slot10;
    got_a2 = a2;
    got_a3 = a3;
}

}

int main() {
    std::uint32_t slot = 0xabcdefu;
    am3d::exe::call_8007a3b0(0x8009f368u, &slot, 0x80010db0u, 0u, record);
    if (calls != 1 || got_a0 != 0x8009f368u || got_slot != &slot ||
        got_a2 != 0x80010db0u || got_a3 != 0u || slot != 0xabcdefu) {
        return 1;
    }
    return 0;
}
