// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8006518c.hpp"

namespace am3d::exe {

bool menu_scan_should_loop(std::uint32_t s7, std::uint32_t limit) {
    return static_cast<std::int32_t>(s7) < static_cast<std::int32_t>(limit);
}

}
