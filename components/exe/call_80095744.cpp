// SPDX-License-Identifier: GPL-3.0-or-later
#include "call_80095744.hpp"

#include "call_800957c8.hpp"

namespace am3d::exe {

void EnterCriticalSection(std::uint32_t a0) {
    (void)a0;
}

void SysDeqIntRP(std::uint32_t a0, std::uint32_t a1) {
    (void)a0;
    (void)a1;
}

void SysEnqIntRP(std::uint32_t a0, std::uint32_t a1) {
    (void)a0;
    (void)a1;
}

void ChangeClearRCnt(std::uint32_t a0, std::uint32_t a1) {
    (void)a0;
    (void)a1;
}

void call_80095744(std::uint32_t& cleared, std::uint32_t& status, std::uint32_t& mask) {
    cleared = 0;
    EnterCriticalSection(0x80022c1cu);
    SysDeqIntRP(2u, 0x800e3ab8u);
    SysEnqIntRP(2u, 0x800e3ab8u);
    status = 0xfffffffeu;
    mask |= 1u;
    ChangeClearRCnt(3u, 0u);
    // gap: ExitCriticalSection at 0x8007fc0c. This note does not state the arguments.
    // The return address is 0x800957ac.
    // The word at 0x800be6b4 is 0. That body is not in the executable.
    std::uint32_t argument = 0;
    (void)call_800957c8(argument, 0, 0);
}

}
