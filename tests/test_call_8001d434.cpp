// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8001d434.hpp"

#include <cstdint>

namespace {

int calls = 0;
std::uint32_t args[4] = {};

std::uint32_t record(std::uint32_t a0) {
    if (calls < 4) args[calls] = a0;
    ++calls;
    if (a0 == 0x41u) return 0x161u;
    if (a0 == 0xffffffc1u) return 0xffffff42u;
    return 0;
}

}

int main() {
    std::uint8_t empty[] = {0};
    am3d::exe::call_8001d434(empty, record);
    if (calls != 0 || empty[0] != 0) return 1;

    calls = 0;
    std::uint8_t text[] = {0x41, 0xc1, 0};
    am3d::exe::call_8001d434(text, record);
    if (calls != 2 || args[0] != 0x41u || args[1] != 0xffffffc1u ||
        text[0] != 0x61 || text[1] != 0x42 || text[2] != 0) {
        return 2;
    }
    return 0;
}
