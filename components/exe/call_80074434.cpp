// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80074434.hpp"
#include "call_80074144.hpp"
namespace am3d::exe {
std::uint32_t call_80074434(std::uint32_t a0) {
    return call_80074144(a0 & 0xffu);
}
}
