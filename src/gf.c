#include "gf.h"

const gf_field GF16  = { "GF(2^4)", 4, 0x13,  "x^4 + x + 1" };
const gf_field GF256 = { "GF(2^8)", 8, 0x11B, "x^8 + x^4 + x^3 + x + 1" };

uint16_t gf_mul(const gf_field *f, uint16_t a, uint16_t b)
{
    uint16_t r = 0;
    int i;

    for (i = 0; i < f->n; i++) {
        if (b & 1) {
            r ^= a;
        }
        b = (uint16_t)(b >> 1);
        a = (uint16_t)(a << 1);
        if (a & 0x100) {
            a ^= f->poly;
        }
    }
    return r;
}