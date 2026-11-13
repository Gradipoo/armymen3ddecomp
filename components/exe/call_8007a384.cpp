// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a384.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-8007a384.md.
Call8007a384Saved call_8007a384(std::uint32_t a0, std::uint32_t a1,
                                std::uint32_t a2, std::uint32_t a3,
                                Call8007a384Fn callee) {
    Call8007a384Saved saved;
    saved.s1 = a0;
    saved.s0 = 1u;
    saved.s3 = a2;
    saved.s2 = a3;
    // gap: unnamed callee at 0x8007a250.
    callee(a0, a1, a2, a3);
    return saved;
}

}
