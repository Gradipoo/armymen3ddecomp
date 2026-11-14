// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// A zero result with a nonzero fourth argument calls the same path again.
unsigned call_800237d0(int result, int fourth);

}
