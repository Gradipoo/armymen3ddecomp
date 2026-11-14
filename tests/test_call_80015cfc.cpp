// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80015cfc.hpp"
#include <cstdint>
int main() {
    const std::uint8_t object[0xb0] = {};
    am3d::exe::call_80015cfc(object);
    return 0;
}
