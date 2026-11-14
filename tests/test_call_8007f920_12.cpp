// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f920_12.hpp"
int main() {
    unsigned words[6] = {};
    am3d::exe::call_8007f920_12(words);
    return words[0] == 0x80808080u && words[5] == 0x80808080u ? 0 : 1;
}
