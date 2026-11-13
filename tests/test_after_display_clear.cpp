// SPDX-License-Identifier: GPL-3.0-or-later
#include "after_display_clear.hpp"

using namespace am3d::exe;

int main() {
    if (call_after_display_clear(0) != 0) return 1;
    if (call_after_display_clear(2) != 2) return 2;
    return 0;
}
