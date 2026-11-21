// SPDX-License-Identifier: GPL-3.0-or-later
#include "disc_data_file_read.hpp"
#include "disc_front_tim_load.hpp"
#include "mission_movement_slice.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

std::filesystem::path probe_dir() {
    return std::filesystem::path("build") / "test_disc_data_file_read";
}

std::filesystem::path write_probe_file(const char* name, const std::vector<std::uint8_t>& bytes) {
    const std::filesystem::path dir = probe_dir();
    std::filesystem::create_directories(dir);
    const std::filesystem::path file = dir / name;
    std::ofstream out(file, std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<const char*>(bytes.data()),
              static_cast<std::streamsize>(bytes.size()));
    return file;
}

std::filesystem::path resolve_disc_root() {
    if (std::filesystem::is_directory("build/disc")) {
        return "build/disc";
    }
    if (std::filesystem::is_directory("disc")) {
        return "disc";
    }
    return {};
}

bool first_line_contains_alpine1(const std::uint8_t* data, std::size_t nbytes) {
    std::string line;
    for (std::size_t i = 0u; i < nbytes; ++i) {
        const char ch = static_cast<char>(data[i]);
        if (ch == '\n' || ch == '\r') {
            break;
        }
        line.push_back(ch);
    }
    return line.find("Alpine1") != std::string::npos;
}

}  // namespace

int main() {
    const std::vector<std::uint8_t> tiny = {'h', 'i'};
    const std::filesystem::path tiny_path = write_probe_file("tiny.bin", tiny);
    std::uint8_t buf[8]{};
    am3d::platform::DiscDataFileReadResult full =
        am3d::platform::read_disc_data_file(tiny_path, sizeof(buf), buf);
    if (!full.ok || full.bytes_read != 2u || full.truncated) {
        return 1;
    }
    if (buf[0] != 'h' || buf[1] != 'i') {
        return 2;
    }

    am3d::platform::DiscDataFileReadResult capped =
        am3d::platform::read_disc_data_file(tiny_path, 1u, buf);
    if (!capped.ok || !capped.truncated || capped.bytes_read != 1u || buf[0] != 'h') {
        return 3;
    }

    am3d::platform::DiscDataFileReadResult missing =
        am3d::platform::read_disc_data_file(probe_dir() / "missing.bin", 4u, buf);
    if (missing.ok) {
        return 4;
    }

    am3d::platform::DiscDataFileReadResult no_buf =
        am3d::platform::read_disc_data_file(tiny_path, 0u, buf);
    if (no_buf.ok) {
        return 5;
    }

    if (!am3d::platform::load_front_tim_disc_bytes({}).empty()) {
        return 10;
    }

    const std::filesystem::path disc_root = resolve_disc_root();
    const std::filesystem::path alp1_path =
        disc_root / am3d::exe::MissionSliceDeclaration::kTxtPath;
    if (disc_root.empty() || !std::filesystem::is_regular_file(alp1_path)) {
        return 0;
    }
    std::vector<std::uint8_t> retail_probe(512u);
    const am3d::platform::DiscDataFileReadResult retail = am3d::platform::read_disc_data_file(
        alp1_path, retail_probe.size(), retail_probe.data());
    if (!retail.ok || retail.bytes_read == 0u) {
        return 6;
    }
    if (!first_line_contains_alpine1(retail_probe.data(), retail.bytes_read)) {
        return 7;
    }
    std::error_code ec;
    const auto retail_size = std::filesystem::file_size(alp1_path, ec);
    if (ec || retail_size == 0u) {
        return 8;
    }
    if (retail_size > retail_probe.size() && !retail.truncated) {
        return 9;
    }
    return 0;
}