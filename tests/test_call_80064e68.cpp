// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80064e68.hpp"

#include <cstdint>

int main() {
    am3d::exe::PadStateDispatch dispatch{};
    am3d::exe::call_80064e68(2u, nullptr, dispatch);
    if (dispatch.word_address != 0x800c3ea0u || dispatch.destination_stated) {
        return 1;
    }
    const std::uint32_t measured = 0x80064f14u;
    am3d::exe::call_80064e68(2u, &measured, dispatch);
    if (dispatch.word_address != 0x800c3ea0u || !dispatch.destination_stated ||
        dispatch.destination != 0x80064f14u) {
        return 2;
    }
    am3d::exe::call_80064e68(0u, nullptr, dispatch);
    if (dispatch.word_address != 0x800c3e98u || dispatch.destination_stated) {
        return 3;
    }
    const std::uint32_t provisional_down = 0x80064f14u;
    am3d::exe::call_80064e68(3u, &provisional_down, dispatch);
    if (dispatch.word_address != 0x800c3ea4u || !dispatch.destination_stated ||
        dispatch.destination != provisional_down) {
        return 4;
    }
    return 0;
}
