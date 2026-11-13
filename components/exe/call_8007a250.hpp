// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call8007a250Block {
    std::uint32_t word0;
    std::uint32_t word4;
    std::uint32_t link;
    std::uint32_t at14;
    std::uint32_t at18;
    std::uint32_t at1c;
};

using Call8007a250Load = std::uint32_t (*)(std::uint32_t address);

std::uint32_t call_8007a250(Call8007a250Block& block, std::uint32_t a1,
                            Call8007a250Load load_word);

}
