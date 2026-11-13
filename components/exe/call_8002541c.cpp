// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8002541c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8002541c.md.
// Copy the loaded word into v0. The delay slot replaces a0. The branch is open.
void call_8002541c(std::uint32_t& a0, std::uint32_t word, std::uint32_t& v0) {
    v0 = word;
    a0 = 0x800d0000u;
    // gap: beq at 0x80025424. v0 is the word at 0x8007f9a8. The taken target is 0x80025470 when that word is 0. The fall-through is 0x8002542c. Which side this boot takes is unknown.
}

}
