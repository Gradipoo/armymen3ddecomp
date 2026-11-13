/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Synthetic PS1 ABI case: signed int is 32 bits. Quotients truncate to zero.
 * Return zero for a zero divisor. Return INT_MIN for INT_MIN divided by -1.
 * Guard both undefined C division cases before evaluating the quotient.
 */
typedef signed int s32;

s32 corpus_signed_division(s32 numerator, s32 denominator) {
    if (denominator == 0) {
        return 0;
    }
    if (numerator == (-2147483647 - 1) && denominator == -1) {
        return (-2147483647 - 1);
    }
    return numerator / denominator;
}
