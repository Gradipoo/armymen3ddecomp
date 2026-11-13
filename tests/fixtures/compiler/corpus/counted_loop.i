/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: char is 8 bits and unsigned int is 32 bits.
 * input points to count readable bytes, or may be null when count is zero.
 * Expected result: sum the bytes modulo 2^32. Read nothing for count zero.
 */
typedef unsigned char u8;
typedef unsigned int u32;

u32 corpus_counted_loop(const u8 *input, u32 count) {
    u32 sum = 0;
    u32 index;
    for (index = 0; index < count; ++index) {
        sum += input[index];
    }
    return sum;
}
