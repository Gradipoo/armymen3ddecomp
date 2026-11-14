// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Write the last five source bytes, then store the three words from call-800620a4.md.
void call_80061ff0(unsigned char* dest, int* index, unsigned* first, unsigned* second, unsigned* third);

}
