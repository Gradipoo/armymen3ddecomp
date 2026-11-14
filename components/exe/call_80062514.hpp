// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// A zero result calls the first handler again with argument 5.
unsigned call_80062514(int result, unsigned* slot, int* argument);

}
