// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "call_80064e68.hpp"
#include "menu_input_scan.hpp"

#include <cstdint>
#include <iostream>

namespace am3d::exe {

// Provisional index-three table word for SDL Down (s2=3). Live RAM unstated.
// See docs/research/re/call-80064e68.md and menu-scan-pad-sdl.md.
constexpr std::uint32_t kMenuScanProvisionalDownDispatchDest = 0x80064f14u;

// Set to 1 at compile time to run the Down inject path in menu_scan_smoke_headless.
constexpr int kMenuScanHeadlessInjectDown = 0;

struct MenuScanDownDispatchInject {
    std::uint32_t down_dest = kMenuScanProvisionalDownDispatchDest;
    PadStateDispatchInject inject{};
};

inline const PadStateDispatchInject& menu_scan_down_dispatch_inject() {
    static MenuScanDownDispatchInject storage{};
    storage.inject.entry[3] = &storage.down_dest;
    return storage.inject;
}

inline void log_menu_input_scan_step(std::ostream& os, const MenuInputScanStep& step) {
    os << "scan_step s2=" << step.head.s2 << " destination_stated="
       << (step.dispatch.destination_stated ? 1 : 0) << " tail_ran="
       << (step.tail_ran ? 1 : 0) << '\n';
}

}  // namespace am3d::exe