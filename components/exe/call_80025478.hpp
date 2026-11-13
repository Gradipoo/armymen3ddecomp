// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80025478.md.
void call_80025478(std::uint32_t& a0, std::uint32_t& stored);

}
