// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007e1f8.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007e1f8.md.
// The load restores the saved return address. a0, a1, v0, and v1 stay unknown.
void call_8007e1f8() {
    return;
}

}
