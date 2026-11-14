// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80025564.hpp"

#include "call_80023848_2.hpp"

namespace am3d::exe {

void call_80025564(int result, unsigned* word) {
    if (result == 0) {
        *word = 0;
        int second = 1;
        int third = 0;
        call_80023848_2(&second, &third);
    }
}

}
