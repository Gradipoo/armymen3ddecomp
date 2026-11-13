/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: char is 8 bits and unsigned int is 32 bits.
 * output points to four writable bytes. Store value in little-endian order.
 * Unsigned shifts and conversions are defined for every 32-bit input.
 */
typedef unsigned char u8;
typedef unsigned int u32;

void corpus_unsigned_bytes(u8 *output, u32 value) {
    output[0] = (u8)value;
    output[1] = (u8)(value >> 8);
    output[2] = (u8)(value >> 16);
    output[3] = (u8)(value >> 24);
}
