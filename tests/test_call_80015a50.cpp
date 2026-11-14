// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80015a50.hpp"
#include <cstdint>
int main() {
    const std::uint8_t object[0xb0] = {};
    am3d::exe::call_80015a50(object);
    return 0;
}
