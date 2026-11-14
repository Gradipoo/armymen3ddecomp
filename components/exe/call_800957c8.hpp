// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800957c8.md.
std::uint32_t call_800957c8(std::uint32_t& argument, std::uint32_t loaded,
                            std::uint32_t handler);

}
