// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Copy the first four bytes of the source and leave the index at 3.
void call_80061f80(unsigned char* dest, int* index);

}
