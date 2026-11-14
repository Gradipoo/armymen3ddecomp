// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e118.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e118.md.
// Store the arriving a0. On this boot that word is 0x800d1598.
void call_8007e118(std::uint32_t& a0, std::uint32_t& stored) {
    stored = a0;
}

}
