// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80063684.hpp"

#include "call_8002554c.hpp"

namespace am3d::exe {

int call_80063684(int result) {
    if (result == 0) {
        unsigned a0 = 0;
        int a2 = 1;
        call_8002554c(&a0, &a2);
        return 0;
    }
    return result;
}

}
