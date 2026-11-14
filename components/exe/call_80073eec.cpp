// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80073eec.hpp"
namespace am3d::exe {
std::uint32_t call_80073eec(std::uint32_t left, std::uint32_t right, std::uint32_t limit) {
    const std::uint32_t sum = left + right;
    if (sum < limit) {
        return sum;
    }
    return sum - limit;
}
}
