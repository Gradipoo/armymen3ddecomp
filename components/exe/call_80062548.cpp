// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80062548.hpp"

#include "call_80063684.hpp"

namespace am3d::exe {

int call_80062548(int result) {
    if (result == 0) {
        return call_80063684(0);
    }
    return 1;
}

}
