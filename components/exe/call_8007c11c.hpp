// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>
#include <functional>

namespace am3d::exe {

class SubmitOrderingTableGpu {
public:
    virtual ~SubmitOrderingTableGpu() = default;
    virtual void draw_sync(std::uint32_t mode) = 0;
    virtual void draw_sync_callback(std::uint32_t retail_callback_address) = 0;
    virtual std::uint32_t draw_otag(std::uint32_t retail_address) = 0;
};

// Addresses are 32-bit guest values. read_flag supplies the word at gp+0x0c
// after synchronization. See docs/research/re/call-8007c11c.md.
std::uint32_t call_8007c11c(std::uint32_t table, std::uint32_t count,
                            const std::function<std::uint32_t()>& read_flag,
                            SubmitOrderingTableGpu& gpu);

}
