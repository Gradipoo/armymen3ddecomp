// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007d52c.hpp"

int main() {
    std::uint32_t cleared = 1;
    am3d::exe::call_8007d52c(0x800c8500u, cleared);
    return cleared == 0 ? 0 : 1;
}
