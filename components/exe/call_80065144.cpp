// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80065144.hpp"

namespace am3d::exe {

MenuFirstByteBranchResult call_80065144(std::uint32_t compare_word_dd730) {
    MenuFirstByteBranchResult result{};
    result.compare_eq_four = compare_word_dd730 == 4u;
    return result;
}

}  // namespace am3d::exe