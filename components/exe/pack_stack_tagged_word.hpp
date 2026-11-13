// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80010e88.md.
std::uint32_t pack_stack_tagged_word(std::uint32_t first, std::uint32_t second,
                                     std::uint32_t third, std::uint32_t fourth,
                                     std::uint32_t fifth);

}
