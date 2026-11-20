// SPDX-License-Identifier: GPL-3.0-or-later
#include "menu_input_scan.hpp"

#include "call_80064f14.hpp"
#include "call_80064f48.hpp"
#include "call_8006508c.hpp"
#include "call_80065098.hpp"
#include "call_800650a8.hpp"
#include "call_800650b4.hpp"
#include "call_800650e0.hpp"
#include "call_800650ec.hpp"
#include "call_800650f4.hpp"
#include "call_80065168.hpp"
#include "call_80064dc8.hpp"
#include "call_80065194.hpp"
#include "call_800651c8.hpp"

namespace am3d::exe {

namespace {

constexpr std::uint32_t kPadStateTwoDestination = 0x80064f14u;

const std::uint32_t* resolve_pad_dispatch_inject(
    std::uint32_t s2, const PadStateDispatchInject* inject) {
    if (s2 == 2u) {
        return &kPadStateTwoDestination;
    }
    if (inject != nullptr && s2 < 7u) {
        return inject->entry[s2];
    }
    return nullptr;
}

void record_loop_exit_when_stopped(MenuInputScanStep& step,
                                   const MenuInputScanState& scan,
                                   std::uint32_t& stack_word_18,
                                   const std::uint8_t* test_inject_s1_lbu) {
    if (!step.loop_again) {
        step.loop_exit = call_80065194(scan.index);
        step.loop_exit_recorded = true;
        if (step.loop_exit.branch_to_651c8) {
            step.loop_taken_651c8 =
                call_800651c8(step.loop_exit.v0, &stack_word_18);
            step.loop_taken_651c8_recorded = true;
            if (step.loop_taken_651c8.branch_to_64dc8) {
                step.loop_body_64dc8 = call_80064dc8(step.loop_taken_651c8.s1,
                                                      test_inject_s1_lbu);
                step.loop_body_64dc8_recorded = true;
            }
        }
    }
}

}

MenuInputScanStep menu_input_scan_step(
    std::uint32_t& stack_word_18, std::uint32_t loop_s7,
    std::uint32_t (*pad_get_state)(std::uint32_t port),
    const std::uint8_t* menu_table, std::uint32_t& menu_table_index,
    std::uint32_t menu_table_bytes, std::uint32_t& stack_word_20,
    std::uint32_t fp, std::uint32_t compare_word_dd730, std::uint8_t*& record,
    std::uint32_t stack_word_58, MenuInputScanState& scan,
    std::uint32_t stack_word_1c, const std::uint32_t* test_inject_s6,
    std::uint32_t* stack_word_28,
    const PadStateDispatchInject* test_inject_pad_dispatch,
    const std::uint8_t* test_inject_s1_lbu) {
    MenuInputScanStep step{};
    call_80064e40(stack_word_18, loop_s7, pad_get_state, step.head);
    if (test_inject_s6 != nullptr) {
        step.head.s6 = *test_inject_s6;
    }
    if (step.head.below_seven == 0u) {
        return step;
    }
    const std::uint32_t* injected =
        resolve_pad_dispatch_inject(step.head.s2, test_inject_pad_dispatch);
    call_80064e68(step.head.s2, injected, step.dispatch);
    if (!step.dispatch.destination_stated ||
        step.dispatch.destination != kPadStateTwoDestination) {
        return step;
    }
    const MenuTableBytesResult bytes = call_80064f14(
        menu_table, menu_table_index, menu_table_bytes);
    if (bytes.first_byte_branch || !bytes.compare_0x41) {
        return step;
    }
    const MenuMaskPathResult mask = call_80064f48(
        stack_word_20, fp, menu_table, menu_table_index, menu_table_bytes,
        compare_word_dd730, record);
    if (mask.compare_eq_four) {
        step.compare_four_ran = true;
        step.compare_four_to_65168 = mask.branch_to_65168;
        step.compare_four_v0 = mask.compare_four_v0;
        if (mask.branch_to_65168) {
            step.tail_ran = true;
            step.loop_again =
                call_80065168(record, scan, stack_word_1c, stack_word_28);
            record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
        }
        return step;
    }
    if (!mask.entered) {
        return step;
    }
    const MenuS6Branch s6_branch = call_8006508c(step.head.s6);
    if (s6_branch.s6_nonzero) {
        const MenuS6TakenPath taken =
            call_80065098(record, mask.complemented, s6_branch.v0,
                           menu_table_index);
        if (taken.branch_to_650b4) {
            (void)call_800650b4(record, mask.complemented);
        } else {
            (void)call_800650a8(record);
        }
        const std::uint32_t complemented = mask.complemented;
        if ((complemented & 0x10u) != 0u) {
            step.tail_ran = true;
            step.loop_again = call_800650d0(record, complemented, stack_word_58,
                                            scan, stack_word_1c);
            record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
            return step;
        }
        if (call_800650e0(complemented)) {
            step.tail_ran = true;
            step.loop_again = call_800650ec(record, stack_word_58, scan, stack_word_1c);
            record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
            return step;
        }
        step.tail_ran = true;
        step.loop_again = call_800650f4(record, stack_word_58, scan, stack_word_1c);
        record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
        return step;
    }
    const std::uint32_t complemented = mask.complemented;
    if ((complemented & 0x10u) != 0u) {
        step.tail_ran = true;
        step.loop_again = call_800650d0(record, complemented, stack_word_58, scan,
                                        stack_word_1c);
        record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
        return step;
    }
    if (call_800650e0(complemented)) {
        step.tail_ran = true;
        step.loop_again = call_800650ec(record, stack_word_58, scan, stack_word_1c);
        record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
        return step;
    }
    step.tail_ran = true;
    step.loop_again = call_800650f4(record, stack_word_58, scan, stack_word_1c);
    record_loop_exit_when_stopped(step, scan, stack_word_18, test_inject_s1_lbu);
    return step;
}

}