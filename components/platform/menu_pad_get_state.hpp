// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::platform {

// Bit index in PadState::buttons. A cleared bit means the control is held.
constexpr unsigned kPadBitDpadUp = 4u;
constexpr unsigned kPadBitDpadDown = 6u;
constexpr unsigned kPadBitDpadLeft = 7u;
constexpr unsigned kPadBitDpadRight = 5u;
constexpr unsigned kPadBitCross = 13u;

// Maps host pad bits to the unsigned word stored in s2 after PadGetState at
// 0x80064e58. Retail samples had s2=2 with below_seven set; see call-80064e58.md.
// Direction indices are provisional until live dispatch words are cited.
std::uint32_t menu_scan_pad_get_state(std::uint32_t port, std::uint16_t buttons);

}  // namespace am3d::platform