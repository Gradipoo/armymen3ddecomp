// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Copy the nine source bytes, then the three stores from call-800620a4.md.
void call_80061f80(unsigned char* dest, int* index, unsigned* first, unsigned* second, unsigned* third, unsigned* slot);

}
