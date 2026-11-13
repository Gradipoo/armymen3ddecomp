/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: short is 16 bits and int is 32 bits.
 * pair points to two readable signed halfwords. Their sum fits signed int.
 * Expected result: sign-extend both fields, then add without overflow.
 */
typedef signed short s16;
typedef signed int s32;

s32 corpus_signed_halfwords(const s16 *pair) {
    return (s32)pair[0] + (s32)pair[1];
}
