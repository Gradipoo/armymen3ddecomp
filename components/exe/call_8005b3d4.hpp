// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8005b3d4.md.
std::uint32_t call_8005b3d4(std::uint32_t& word, std::uint32_t value);

}
