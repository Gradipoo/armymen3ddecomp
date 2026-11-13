// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a384.hpp"

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
    const am3d::exe::Call8007a384Saved saved =
        am3d::exe::call_8007a384(0x8009f368u, 1u, 0x80010db0u, 0u, record);
    if (calls != 1 || got_a0 != 0x8009f368u || got_a1 != 1u ||
        got_a2 != 0x80010db0u || got_a3 != 0u) {
        return 1;
    }
    if (saved.s0 != 1u || saved.s1 != 0x8009f368u || saved.s2 != 0u ||
        saved.s3 != 0x80010db0u) {
        return 2;
    }
    return 0;
}
