// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

namespace am3d::exe {

// Copy the nine source bytes. call-80061ff0.md writes the last five.
void call_80061f80(unsigned char* dest, int* index);

}
