// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e68.hpp"

namespace am3d::exe {

void call_80064e68(std::uint32_t s2, const std::uint32_t* injected_word,
                   PadStateDispatch& dispatch) {
    dispatch.word_address = 0x800c3e98u + (s2 * 4u);
    // gap: loaded pointer unstated unless injected.
    if (injected_word == nullptr) {
        dispatch.destination = 0u;
        dispatch.destination_stated = false;
        return;
    }
    dispatch.destination = *injected_word;
    dispatch.destination_stated = true;
}

}
