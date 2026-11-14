// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025564.hpp"

int main() {
    unsigned word = 1;
    am3d::exe::call_80025564(0, &word);
    if (word != 0) {
        return 1;
    }
    return 0;
}
