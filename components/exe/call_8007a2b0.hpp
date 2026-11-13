// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call8007a2b0Block {
    std::uint32_t word0;
    std::uint32_t link;
    std::uint32_t at14;
    std::uint32_t at18;
    std::uint32_t at1c;
};

using Call8007a2b0Load = std::uint32_t (*)(std::uint32_t address);

std::uint32_t call_8007a2b0(Call8007a2b0Block& block, std::uint32_t* slot,
                            Call8007a2b0Load load_word);

}
