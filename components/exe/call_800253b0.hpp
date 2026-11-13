// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call800253b0Args {
    std::uint32_t a0;
    std::uint32_t a1;
};

// Behavior reference: docs/research/re/call-800253b0.md.
void call_800253b0(Call800253b0Args calls[5]);

}
