// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_8007c11c.hpp"

namespace am3d::exe {

std::uint32_t call_8007c11c(std::uint32_t table, std::uint32_t count,
                            const std::function<std::uint32_t()>& read_flag,
                            SubmitOrderingTableGpu& gpu) {
    gpu.draw_sync(0);
    if (read_flag() != 0) {
        gpu.draw_sync_callback(0x8007c00cu);
    }
    return gpu.draw_otag(table + count * 4u - 4u);
}

}
