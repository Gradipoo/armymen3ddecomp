// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8003852c.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8003852c.md.
void call_8003852c(std::uint8_t flag, std::uint32_t a0, std::int32_t a1, std::uint32_t a2,
                   std::uint32_t a3, std::uint32_t fifth, Call8003852cArgs& args) {
    args.invoke = false;
    if (flag == 0) {
        // gap: the branch target 0x8003856c is not traced.
        return;
    }
    if (static_cast<std::int32_t>(a3) > 0) {
        // gap: the fall-through at 0x80038550 is not traced.
        return;
    }
    args.invoke = true;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    args.a3 = fifth;
    // gap: call 0x800381b0. a0, a1, and a2 stay as they arrived. a3 is the fifth argument. The return address is 0x8003856c.
}

}
