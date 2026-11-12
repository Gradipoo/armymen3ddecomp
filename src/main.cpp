// SPDX-License-Identifier: GPL-3.0-or-later
#include "browser.hpp"
#include "keyboard.hpp"
#include "load.hpp"
#include "overlay.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

#ifdef _WIN32
constexpr const char* kDevNull = "NUL";
#else
constexpr const char* kDevNull = "/dev/null";
#endif

int run(const std::string& cmd) {
    int status = std::system(cmd.c_str());
    if (status == 0) {
        return 0;
    }
    return 1;
}

std::string quote(const std::string& value) {
#ifdef _WIN32
    std::string out = "\"";
    for (char ch : value) {
        if (ch == '"') {
            out += "\"\"";
        } else {
            out += ch;
        }
    }
    out += "\"";
    return out;
#else
    std::string out = "'";
    for (char ch : value) {
        if (ch == '\'') {
            out += "'\\''";
        } else {
            out += ch;
        }
    }
    out += "'";
    return out;
#endif
}

std::filesystem::path repo_from(std::filesystem::path start) {
    std::error_code ec;
    start = std::filesystem::absolute(start, ec);
    if (ec) {
        return {};
    }
    if (std::filesystem::is_regular_file(start, ec)) {
        start = start.parent_path();
    }
    while (true) {
        auto script = start / "tools" / "disc.py";
        if (std::filesystem::is_regular_file(script, ec) && !ec) {
            return start;
        }
        auto parent = start.parent_path();
        if (parent.empty() || parent == start) {
            break;
        }
        start = parent;
    }
    return {};
}

std::filesystem::path find_repo(const char* argv0) {
    std::error_code ec;
    auto from_cwd = repo_from(std::filesystem::current_path(ec));
    if (!from_cwd.empty()) {
        return from_cwd;
    }
    if (argv0 == nullptr || argv0[0] == '\0') {
        return {};
    }
    return repo_from(std::filesystem::path(argv0));
}

std::string find_python() {
    std::string probe = std::string("python3 -c \"import sys\" >") + kDevNull + " 2>&1";
    if (run(probe) == 0) {
        return "python3";
    }
    return "python";
}

std::filesystem::path find_psx_exe(const std::filesystem::path& disc_dir) {
    std::error_code ec;
    if (!std::filesystem::is_directory(disc_dir, ec) || ec) {
        return {};
    }
    std::vector<std::filesystem::path> found;
    std::filesystem::recursive_directory_iterator it(
        disc_dir, std::filesystem::directory_options::skip_permission_denied, ec);
    const std::filesystem::recursive_directory_iterator end;
    for (; it != end && !ec; it.increment(ec)) {
        if (ec) {
            break;
        }
        std::error_code file_ec;
        if (!it->is_regular_file(file_ec) || file_ec) {
            continue;
        }
        std::ifstream in(it->path(), std::ios::binary);
        if (!in) {
            continue;
        }
        std::string magic(8, '\0');
        in.read(magic.data(), 8);
        if (in.gcount() == 8 && magic == "PS-X EXE") {
            found.push_back(it->path());
        }
    }
    if (found.empty()) {
        return {};
    }
    std::sort(found.begin(), found.end());
    return found.front();
}

}  // namespace

int main(int argc, char** argv) {
    (void)am3d::exe::load_status();
    (void)am3d::input::keyboard_status();
    (void)am3d::net::browser_status();
    (void)am3d::mods::overlay_status();

    const char* cue = nullptr;
    if (argc >= 2) {
        cue = argv[1];
    }

    auto root = find_repo(argc > 0 ? argv[0] : nullptr);
    if (root.empty()) {
        std::cerr << "error: tools/disc.py not found\n";
        return 1;
    }

    auto disc_py = std::filesystem::absolute(root / "tools" / "disc.py");
    auto exe_info_py = std::filesystem::absolute(root / "tools" / "exe_info.py");
    std::string python = find_python();

    std::string extract_cmd = python + " " + quote(disc_py.string());
    if (cue != nullptr) {
        extract_cmd += " ";
        extract_cmd += quote(cue);
    }
    extract_cmd += " >";
    extract_cmd += kDevNull;
    if (run(extract_cmd) != 0) {
        return 1;
    }

    auto exe_path = find_psx_exe(root / "build" / "disc");
    if (exe_path.empty()) {
        std::cerr << "error: no PS-X EXE in build/disc\n";
        return 1;
    }

    auto abs_exe = std::filesystem::absolute(exe_path);
    std::string info_cmd =
        python + " " + quote(exe_info_py.string()) + " " + quote(abs_exe.string());
    if (run(info_cmd) != 0) {
        return 1;
    }
    return 0;
}
