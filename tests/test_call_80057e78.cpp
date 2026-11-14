// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80057e78.hpp"
#include <cstdint>
#include <cstring>
int main() {
    std::uint8_t record[0x20];
    std::memset(record, 0xab, sizeof record);
    if (am3d::exe::call_80057e78(record, 0x11u) != record) return 1;
    std::uint32_t word = 0;
    std::memcpy(&word, record + 0x1c, 4);
    if (word != 0x800c3554u) return 1;
    std::memcpy(&word, record + 8, 4);
    if (word != 0x11u) return 1;
    if (record[0] != 0 || record[2] != 0 || record[4] != 0 || record[0xc] != 0) return 1;
    std::memcpy(&word, record + 0x10, 4);
    if (word != 0) return 1;
    std::memcpy(&word, record + 0x14, 4);
    if (word != 0) return 1;
    return 0;
}
