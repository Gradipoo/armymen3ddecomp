// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_task7_checkpoint.hpp"

#include <sstream>

namespace am3d::exe {

std::string format_menu_task7_checkpoint(const PrototypeTask7MenuResult& result) {
    std::ostringstream out;
    out << result.s7_after_a << ' ' << result.s7_after_b << ' '
        << static_cast<unsigned>(result.tail_0b) << ' '
        << static_cast<unsigned>(result.tail_87) << ' ' << result.marker_x_a << ' '
        << result.marker_x_b << ' ' << result.selection_index_after_b << ' '
        << (result.has_front ? 1 : 0) << '\n';
    return out.str();
}

}  // namespace am3d::exe
