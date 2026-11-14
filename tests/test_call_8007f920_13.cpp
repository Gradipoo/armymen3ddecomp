// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007f920_13.hpp"
int main() {
    unsigned words[6] = {1, 1, 1, 1, 1, 1};
    am3d::exe::call_8007f920_13(words);
    return words[0] == 0 && words[5] == 0 ? 0 : 1;
}
