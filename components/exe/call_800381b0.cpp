// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_800381b0.hpp"

namespace am3d::exe {

// Behavior reference: docs/research/re/call-800381b0.md.
void call_800381b0(std::uint32_t& flag_word, std::uint32_t slot, std::uint32_t node_word,
                   std::uint32_t link, std::uint32_t handler_target, std::uint32_t handler_arg,
                   std::uint32_t a0, std::int32_t a1, std::uint32_t a2, Call800381b0Args& args) {
    args.invoke = false;
    if (flag_word != 0) {
        // gap: the branch target 0x80038380 is not traced.
        return;
    }
    flag_word = 1;
    if (slot == 0) {
        // gap: the branch target 0x80038288 is not traced.
        return;
    }
    const std::uint32_t half = static_cast<std::uint32_t>(a1);
    if (node_word != 0xffffffffu && node_word != half) {
        // gap: the branch target 0x80038278 is not traced.
        return;
    }
    if (link == 0) {
        // gap: the branch target 0x80038278 is not traced.
        return;
    }
    args.invoke = true;
    args.target = handler_target;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    args.a3 = handler_arg;
    // gap: jalr through the word at offset 0 of the handler. a0 is the incoming a0. a1 is the halfword. a2 is the incoming a2. a3 is the word at offset 4. The return address is 0x80038268.
}

}
