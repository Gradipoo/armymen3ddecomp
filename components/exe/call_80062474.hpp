// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Clear the listed words, call the second 0x80075198 entry, and return that address.
unsigned call_80062474(unsigned* slot);

}
