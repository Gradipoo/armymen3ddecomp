// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80059f88.hpp"
namespace am3d::exe {
void call_80059f88(std::uint32_t selector, std::uint32_t& slot, std::uint32_t& stored) {
    const std::uint32_t index = ((selector >> 2) & 4u) | (selector & 3u);
    slot = 0x800d8458u + index * 4u;
    stored = 0xffff0000u;
}
}
