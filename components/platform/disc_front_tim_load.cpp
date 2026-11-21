// SPDX-License-Identifier: GPL-3.0-or-later
#include "disc_front_tim_load.hpp"

#include "disc_data_file_read.hpp"

#include <array>

namespace am3d::platform {

std::vector<std::uint8_t> load_front_tim_disc_bytes(const std::filesystem::path& disc_root) {
    std::vector<std::uint8_t> bytes;
    if (disc_root.empty()) {
        return bytes;
    }
    std::array<std::uint8_t, kFrontTimMeasuredBytes> buffer{};
    const DiscDataFileReadResult read = read_disc_data_file(
        disc_root / "DATA/FRONT.TIM", buffer.size(), buffer.data());
    if (!read.ok || read.truncated || read.bytes_read != kFrontTimMeasuredBytes) {
        return bytes;
    }
    bytes.assign(buffer.begin(), buffer.begin() + read.bytes_read);
    return bytes;
}

}  // namespace am3d::platform