#ifndef GF_H
#define GF_H

#include <stdint.h>

/*Mo ta mot truong GF(2^n)*/
typedef struct {
    const char *name;
    int n;
    uint16_t poly; /*da thuc toi gian bac n*/
    const char *poly_str; /*da thuc toi gian dang chu, de in ra*/
} gf_field;

extern const gf_field GF16; /*GF(2^4), m(x) = x^4 + x + 1*/
extern const gf_field GF256; /*GF(2^8), m(x) = x^8 + x^4 + x^3 + x + 1*/

uint16_t gf_mul(const gf_field *f, uint16_t a, uint16_t b);

#endif