// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "prototype_task_7_menu.hpp"

#include <string>

namespace am3d::exe {

// One line: s7_a s7_b tail0b tail87 marker_a marker_b selection_b has_front
// Tail bytes are decimal. has_front is 0 or 1. Trailing newline included.
std::string format_menu_task7_checkpoint(const PrototypeTask7MenuResult& result);

}  // namespace am3d::exe
