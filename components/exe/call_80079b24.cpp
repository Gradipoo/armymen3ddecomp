// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80079b24.hpp"

#include "call_80079270.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-80079b24.md.
void call_80079b24(std::uint32_t a0) {
    (void)a0;
    (void)call_80079270();
}

}
