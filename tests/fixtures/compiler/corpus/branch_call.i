/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: unsigned int is 32 bits.
 * For odd value, call the unresolved external function and add three modulo
 * 2^32. For even value, return value XOR 0x55 without making the call.
 * The caller does not assume an implementation or address for the external.
 */
typedef unsigned int u32;
extern u32 corpus_external(u32 value);

u32 corpus_branch_call(u32 value) {
    if (value & 1u) {
        return corpus_external(value) + 3u;
    }
    return value ^ 0x55u;
}
