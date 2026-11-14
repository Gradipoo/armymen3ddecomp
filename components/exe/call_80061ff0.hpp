// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Write the last five source bytes and leave the index at 8.
void call_80061ff0(unsigned char* dest, int* index);

}
