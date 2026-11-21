// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <vector>

namespace am3d::platform {

// Measured owner file size. See docs/research/re/front-tim.md.
constexpr std::size_t kFrontTimMeasuredBytes = 2880u;

// Loads DATA/FRONT.TIM under disc_root through read_disc_data_file. Returns
// empty when disc_root is empty, the file is missing, or the read is not
// exactly kFrontTimMeasuredBytes without truncation.
std::vector<std::uint8_t> load_front_tim_disc_bytes(const std::filesystem::path& disc_root);

}  // namespace am3d::platform