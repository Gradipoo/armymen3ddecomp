// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct MenuS6Branch {
    std::uint32_t v0;
    bool s6_nonzero;
};

// Behavior reference: docs/research/re/call-8006508c.md.
MenuS6Branch call_8006508c(std::uint32_t s6);

}
