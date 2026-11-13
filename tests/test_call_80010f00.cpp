// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010f00.hpp"

#include <array>
#include <cstdint>

namespace {

int calls = 0;
std::uint32_t got_a0 = 0;
std::uint32_t got_a1 = 0;
std::uint32_t got_a2 = 0;
std::uint32_t got_a3 = 0;

std::uint32_t record(std::uint32_t a0, std::uint32_t a1, std::uint32_t a2,
                     std::uint32_t a3) {
    ++calls;
    got_a0 = a0;
    got_a1 = a1;
    got_a2 = a2;
    got_a3 = a3;
    return 0x5aabcdefu;
}

}

int main() {
    std::array<std::uint8_t, am3d::exe::kCall80010f00Bytes> object{};
    object.fill(0x11);
    const std::uint32_t packed = am3d::exe::call_80010f00(
        record, object.data(), 0x22222222u, 0x33333333u, 0x44444444u,
        0x55555555u);
    if (calls != 1 || got_a0 != 0x22222222u || got_a1 != 0x33333333u ||
        got_a2 != 0x44444444u || got_a3 != 0x55555555u ||
        packed != 0x5aabcdefu) {
        return 1;
    }
    for (std::size_t i = 0; i < object.size(); ++i) {
        std::uint8_t expect = 0x11;
        if (i == 0x6c) expect = 0xef;
        if (i == 0x6d) expect = 0xcd;
        if (i == 0x6e) expect = 0xab;
        if (i == 0x6f) expect = 0x5a;
        if (object[i] != expect) return 1;
    }
    return 0;
}
