#include <stdio.h>
#include <string.h>
#include "gf.h"

const truong_gf GF16  = { "GF(2^4)", 4, 0x13,  "x^4 + x + 1" };
const truong_gf GF256 = { "GF(2^8)", 8, 0x11B, "x^8 + x^4 + x^3 + x + 1" };

uint16_t nhan_gf(const truong_gf *t, uint16_t a, uint16_t b)
{
    uint16_t r = 0;
    uint16_t overflow = (uint16_t)(1u << t->n); /*bit x^n*/
    int i;

    for (i = 0; i < t->n; i++) {
        if (b & 1) {
            r ^= a;
        }
        b = (uint16_t)(b >> 1);
        a = (uint16_t)(a << 1);
        if (a & overflow) {
            a ^= t->da_thuc;
        }
    }
    return r;
}

void da_thuc_string(uint16_t value, char *chuoi, size_t Size)
{
    char row[16];
    int i, first = 1;

    if (Size == 0) {
        return;
    }
    chuoi[0] = '\0';

    for (i = 15; i >= 0; i--) {
        if (!((value >> i) & 1)) {
            continue;
        }
        if (i == 0) {
            snprintf(row, sizeof row, "1");
        } else if (i == 1) {
            snprintf(row, sizeof row, "x");
        } else {
            snprintf(row, sizeof row, "x^%d", i);
        }
        if (!first) {
            strncat(chuoi, " + ", Size - strlen(chuoi) - 1);
        }
        strncat(chuoi, row, Size - strlen(chuoi) - 1);
        first = 0;
    }
}