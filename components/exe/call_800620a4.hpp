// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Store 0, 0, and the source address, then run the 0x80062474 epilogue.
unsigned call_800620a4(unsigned* first, unsigned* second, unsigned* third, unsigned* slot);

}
