// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010e00.hpp"

#include <cstdint>

namespace {

int calls = 0;
std::uint32_t got_a0 = 0;
std::uint32_t got_a1 = 0;
std::uint32_t got_a2 = 0;
std::uint32_t got_a3 = 0;

void record(std::uint32_t a0, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
    ++calls;
    got_a0 = a0;
    got_a1 = a1;
    got_a2 = a2;
    got_a3 = a3;
}

}

int main() {
    am3d::exe::call_80010e00(record);
    if (calls != 1 || got_a0 != 0x8009f368u || got_a1 != 1u ||
        got_a2 != 0x80010db0u || got_a3 != 0u) {
        return 1;
    }
    return 0;
}
