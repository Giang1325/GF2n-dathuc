#ifndef GF_H
#define GF_H

#include <stddef.h>
#include <stdint.h>

/* Mo ta mot truong GF(2^n) */
typedef struct {
    const char *ten;
    int n;
    uint16_t da_thuc; /*da thuc toi gian bac n*/
    const char *da_thuc_chu; /*da thuc toi gian dang chu, de in ra*/
} truong_gf;

extern const truong_gf GF16; /*GF(2^4), m(x) = x^4 + x + 1*/
extern const truong_gf GF256; /*GF(2^8), m(x) = x^8 + x^4 + x^3 + x + 1*/

uint16_t nhan_gf(const truong_gf *t, uint16_t a, uint16_t b);

void da_thuc_string(uint16_t value, char *chuoi, size_t Size);

#endif