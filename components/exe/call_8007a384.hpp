// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstdint>

namespace am3d::exe {

struct Call8007a384Saved {
    std::uint32_t s0;
    std::uint32_t s1;
    std::uint32_t s2;
    std::uint32_t s3;
};

using Call8007a384Fn = void (*)(std::uint32_t a0, std::uint32_t a1,
                                std::uint32_t a2, std::uint32_t a3);

Call8007a384Saved call_8007a384(std::uint32_t a0, std::uint32_t a1,
                                std::uint32_t a2, std::uint32_t a3,
                                Call8007a384Fn callee);

}
