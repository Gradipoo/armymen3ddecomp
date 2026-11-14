// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

void call_8007d52c(std::uint32_t address, std::uint32_t& cleared);

}
