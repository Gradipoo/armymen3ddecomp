// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// A zero result skips the other call and returns the first handler.
unsigned call_800624cc(int result, int* argument);

}
