// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct PadStateDispatch {
    std::uint32_t word_address;
    std::uint32_t destination;
    bool destination_stated;
};

// Behavior reference: docs/research/re/call-80064e68.md.
// injected_word supplies the table load. A null pointer leaves it unstated.
void call_80064e68(std::uint32_t s2, const std::uint32_t* injected_word,
                   PadStateDispatch& dispatch);

}
