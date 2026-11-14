// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80012fe8.hpp"
#include "call_800793ec.hpp"
namespace am3d::exe {
std::uint8_t* call_80012fe8(std::uint8_t* object) {
    auto* words = reinterpret_cast<std::uint32_t*>(object + 0x80);
    call_800793ec(words, 0x80073df8u, 0x8009f408u, 0u);
    return object;
}
}
