// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

namespace am3d::platform {

struct DiscDataFileReadResult {
    bool ok = false;
    std::size_t bytes_read = 0;
    bool truncated = false;
    std::string error;
};

// Reads a regular file in binary mode. At most max_bytes are written to
// out_buffer. Callers join disc_root with a DATA/ relative name; this helper
// does not verify paths stay under disc_root.
DiscDataFileReadResult read_disc_data_file(const std::filesystem::path& path,
                                           std::size_t max_bytes,
                                           std::uint8_t* out_buffer);

}  // namespace am3d::platform