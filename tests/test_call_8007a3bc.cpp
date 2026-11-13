// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007a3bc.hpp"

#include <cstdint>

namespace {

int calls = 0;

std::uint32_t nonzero() {
    ++calls;
    return 0x99u;
}

}

int main() {
    calls = 0;
    const std::uint32_t result = am3d::exe::call_8007a3bc(0u, 1u, nonzero);
    if (calls != 0 || result != 1u) return 1;
    return 0;
}
