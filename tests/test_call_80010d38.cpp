// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80010d38.hpp"

#include <array>
#include <cstdint>

namespace {

int calls = 0;
std::uint32_t got_a0 = 0;
int nonzero_calls = 0;
std::uint32_t nonzero_a0 = 0;

void record(std::uint32_t a0) {
    ++calls;
    got_a0 = a0;
}

void record_nonzero(std::uint32_t a0) {
    ++nonzero_calls;
    nonzero_a0 = a0;
}

void set_word(std::array<std::uint8_t, am3d::exe::kCall80010d38Bytes>& object, std::uint32_t value) {
    object[am3d::exe::kCall80010d38WordOffset] = static_cast<std::uint8_t>(value);
    object[am3d::exe::kCall80010d38WordOffset + 1] = static_cast<std::uint8_t>(value >> 8);
    object[am3d::exe::kCall80010d38WordOffset + 2] = static_cast<std::uint8_t>(value >> 16);
    object[am3d::exe::kCall80010d38WordOffset + 3] = static_cast<std::uint8_t>(value >> 24);
}

}

int main() {
    std::array<std::uint8_t, am3d::exe::kCall80010d38Bytes> object{};
    object.fill(0x5a);
    set_word(object, 0x89abcdefu);
    const auto before = object;
    am3d::exe::call_80010d38(object.data(), 0, record, record_nonzero);
    auto cleared = before;
    set_word(cleared, 0);
    if (calls != 1 || got_a0 != 0x89abcdefu || nonzero_calls != 0 || object != cleared) return 1;

    calls = 0;
    set_word(object, 0);
    const auto already = object;
    am3d::exe::call_80010d38(object.data(), 0, record, record_nonzero);
    if (calls != 0 || nonzero_calls != 0 || object != already) return 2;

    calls = 0;
    set_word(object, 0x01020304u);
    const auto kept = object;
    am3d::exe::call_80010d38(object.data(), 0x11u, record, record_nonzero);
    if (calls != 0 || nonzero_calls != 1 || nonzero_a0 != 0x11u || object != kept) return 3;
    return 0;
}
