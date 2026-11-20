// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e14.hpp"

#include <cstdint>

namespace {

std::uint32_t g_pad_state = 2u;

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return g_pad_state;
}

}

int main() {
  constexpr std::uint32_t kS5 = 2u;
  std::uint32_t sp28 = 0xffu;
  constexpr std::uint32_t kRecord = 0x800dd748u + kS5 * 124u;
  constexpr std::uint32_t kAux = 0x800dd708u + kS5 * 4u;
  const am3d::exe::MenuLoopReentry64e14 body =
      am3d::exe::call_80064e14(kS5, 1u, 0u, &sp28, pad_get_state);
  if (body.s0 != kRecord || body.s4 != kAux || sp28 != kS5 * 4u) {
    return 1;
  }
  if (body.head.s6 != 0u || body.head.s3 != 0x10u || body.head.s2 != g_pad_state ||
      body.head.below_seven != 1u || !body.head.entered_64e68 ||
      body.head.branch_to_64f14) {
    return 2;
  }
  g_pad_state = 7u;
  const am3d::exe::MenuLoopReentry64e14 high =
      am3d::exe::call_80064e14(0u, 0u, 0u, nullptr, pad_get_state);
  if (high.head.below_seven != 0u || high.head.s2 != 7u ||
      !high.head.branch_to_64f14 || high.head.entered_64e68) {
    return 3;
  }
  return 0;
}