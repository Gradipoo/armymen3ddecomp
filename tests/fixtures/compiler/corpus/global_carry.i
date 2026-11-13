/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: unsigned int is 32 bits.
 * corpus_global_words names at least 8193 readable words. Return word 8192.
 * Its byte offset is 0x8000. The object keeps the external symbol unresolved.
 * A later synthetic placement can exercise signed-low-half carry handling.
 */
typedef unsigned int u32;
extern u32 corpus_global_words[8193];

u32 corpus_global_carry(void) {
    return corpus_global_words[8192];
}
