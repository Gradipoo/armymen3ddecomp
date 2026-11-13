// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a2b0.hpp"

namespace am3d::exe {

namespace {

std::uint32_t adjusted_count(std::uint32_t count, std::uint32_t word0) {
    if (count == 0xffffffffu) return count;
    if ((word0 & 2u) != 0) return count + 1u;
    return count - 1u;
}

std::uint32_t linked_node(std::uint32_t word0, std::uint32_t node, std::uint32_t link,
                          Call8007a2b0Load load_word) {
    if ((word0 & 2u) != 0) {
        if (node == link) return 0;
        return load_word(node + 4u);
    }
    if ((word0 & 1u) != 0) {
        node = load_word(node + 8u);
    } else {
        std::uint32_t cursor = load_word(link + 4u);
        std::uint32_t previous = link;
        while (cursor != node) {
            previous = cursor;
            cursor = load_word(previous + 4u);
        }
        node = previous;
    }
    if (node == link) return 0;
    return node;
}

}

// Behavior reference: docs/research/re/call-8007a2b0.md.
std::uint32_t call_8007a2b0(Call8007a2b0Block& block, std::uint32_t* slot,
                            Call8007a2b0Load load_word) {
    const std::uint32_t count = adjusted_count(block.at18, block.word0);
    const std::uint32_t node = block.at1c;
    block.at14 = node;
    block.at18 = count;
    if (node == 0) {
        *slot = 0;
        return 0;
    }
    *slot = load_word(node);
    block.at1c = linked_node(block.word0, node, block.link, load_word);
    return 1u;
}

}
