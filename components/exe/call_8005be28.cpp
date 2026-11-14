// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8005be28.hpp"
namespace am3d::exe {
std::uint32_t call_8005be28(std::uint32_t a0, std::uint32_t& word) {
    const std::uint32_t old = word;
    word = a0;
    return old;
}
}
