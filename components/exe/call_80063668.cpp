// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063668.hpp"

#include "call_80062434.hpp"

namespace am3d::exe {

void call_80063668(std::uint8_t* dest, std::uint32_t& a1, std::uint32_t a0) {
    a1 = a0;
    std::uint32_t next_a0 = 0;
    call_80062434(dest, next_a0, a1);
}

}
