// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan.hpp"

#include <array>
#include <cstdint>

namespace {

std::uint32_t g_state = 0u;

std::uint32_t pad_get_state(std::uint32_t port) {
    (void)port;
    return g_state;
}

constexpr std::array<std::uint8_t, 4u> kReleased{0u, 0x41u, 0xffu, 0xffu};
constexpr std::array<std::uint8_t, 4u> kUp{0u, 0x41u, 0xefu, 0xffu};
constexpr std::array<std::uint8_t, 4u> kHeld{0u, 0x41u, 0xbfu, 0xffu};

}

int main() {
    std::array<std::uint8_t, 0x100u> bytes{};
    std::uint8_t* record = bytes.data();
    am3d::exe::MenuInputScanState scan{};
    std::uint32_t table_index = 0u;
    std::uint32_t sp20 = 0u;
    g_state = 2u;
    am3d::exe::MenuInputScanStep up = am3d::exe::menu_input_scan_step(
        1u, 2u, pad_get_state, kUp.data(), table_index, kUp.size(), sp20, 0u,
        0u, record, 0u, scan, 4u);
    if (!up.tail_ran || !up.loop_again || bytes[0x0bu] != 0x80u) {
        return 1;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    am3d::exe::MenuInputScanStep clear = am3d::exe::menu_input_scan_step(
        0u, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, 8u);
    if (!clear.tail_ran || !clear.loop_again || bytes[0x0bu] != 0u) {
        return 2;
    }

    bytes.fill(0x11u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    am3d::exe::MenuInputScanStep held = am3d::exe::menu_input_scan_step(
        0u, 0u, pad_get_state, kHeld.data(), table_index, kHeld.size(), sp20,
        0u, 0u, record, 0u, scan, 8u);
    if (!held.tail_ran || !held.loop_again || bytes[0x0bu] != 0x7fu ||
        record != bytes.data() + 0x7cu) {
        return 3;
    }

    g_state = 7u;
    table_index = 0u;
    am3d::exe::MenuInputScanStep high = am3d::exe::menu_input_scan_step(
        0u, 0u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, 0u, record, 0u, scan, 8u);
    if (high.tail_ran) {
        return 4;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    g_state = 2u;
    constexpr std::uint32_t kForceS6 = 1u;
    constexpr std::array<std::uint8_t, 4u> kUpS6{0u, 0x41u, 0x6fu, 0xffu};
    am3d::exe::MenuInputScanStep s6_up = am3d::exe::menu_input_scan_step(
        1u, 2u, pad_get_state, kUpS6.data(), table_index, kUpS6.size(), sp20,
        0u, 0u, record, 0u, scan, 4u, &kForceS6);
    if (!s6_up.tail_ran || !s6_up.loop_again || bytes[0x0au] != 0x80u ||
        bytes[0x0bu] != 0x80u) {
        return 5;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    constexpr std::array<std::uint8_t, 4u> kS6Released{0u, 0x41u, 0xffu, 0xffu};
    am3d::exe::MenuInputScanStep s6_clear = am3d::exe::menu_input_scan_step(
        0u, 0u, pad_get_state, kS6Released.data(), table_index,
        kS6Released.size(), sp20,
        0u, 0u, record, 0u, scan, 8u, &kForceS6);
    if (!s6_clear.tail_ran || !s6_clear.loop_again || bytes[0x0au] != 0u ||
        bytes[0x0bu] != 0u) {
        return 6;
    }

    bytes.fill(0u);
    record = bytes.data();
    scan = {};
    table_index = 0u;
    sp20 = 0u;
    g_state = 2u;
    constexpr std::uint32_t kCompareFour = 4u;
    am3d::exe::MenuInputScanStep alt = am3d::exe::menu_input_scan_step(
        1u, 2u, pad_get_state, kReleased.data(), table_index, kReleased.size(),
        sp20, 0u, kCompareFour, record, 0u, scan, 8u);
    if (alt.tail_ran || !alt.compare_four_ran || !alt.compare_four_to_65168 ||
        alt.compare_four_v0 != 1u || table_index != 2u) {
        return 7;
    }

    return 0;
}