// SPDX-License-Identifier: GPL-3.0-or-later
#include "disc_data_file_read.hpp"

#include <fstream>
#include <string>

namespace am3d::platform {

DiscDataFileReadResult read_disc_data_file(const std::filesystem::path& path,
                                           std::size_t max_bytes,
                                           std::uint8_t* out_buffer) {
    DiscDataFileReadResult result{};
    if (out_buffer == nullptr || max_bytes == 0u) {
        result.error = "buffer or max_bytes invalid";
        return result;
    }
    std::error_code ec;
    if (!std::filesystem::is_regular_file(path, ec) || ec) {
        result.error = "not a regular file";
        return result;
    }
    const auto file_size = std::filesystem::file_size(path, ec);
    if (ec) {
        result.error = "file_size failed";
        return result;
    }
    if (file_size > max_bytes) {
        result.truncated = true;
    }
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        result.error = "open failed";
        return result;
    }
    const std::size_t to_read =
        static_cast<std::size_t>(result.truncated ? max_bytes : file_size);
    if (!in.read(reinterpret_cast<char*>(out_buffer),
                static_cast<std::streamsize>(to_read))) {
        result.error = "read failed";
        return result;
    }
    result.bytes_read = to_read;
    result.ok = true;
    return result;
}

}  // namespace am3d::platform