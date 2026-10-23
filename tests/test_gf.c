#include <stdio.h>
#include "gf.h"

static int pass = 0;
static int fail = 0;

static void check(int ok, const char *name)
{
    if (ok) {
        pass++;
        printf("[PASS] %s\n", name);
    } else {
        fail++;
        printf("[FAIL] %s\n", name);
    }
}

static uint16_t ref_mul(const truong_gf *t, uint16_t a, uint16_t b)
{
    uint32_t tich = 0;
    int i;

    for (i = 0; i < t->n; i++) {
        if ((b >> i) & 1) {
            tich ^= (uint32_t)a << i;
        }
    }
    for (i = 2 * t->n - 2; i >= t->n; i--) {
        if ((tich >> i) & 1) {
            tich ^= (uint32_t)t->da_thuc << (i - t->n);
        }
    }
    return (uint16_t)tich;
}

static void test_vidu(void)
{
    check(nhan_gf(&GF256, 0x57, 0x83) == 0xC1, "GF(2^8): 57 * 83 = C1");
    check(nhan_gf(&GF256, 0x57, 0x13) == 0xFE, "GF(2^8): 57 * 13 = FE");
    check(nhan_gf(&GF256, 0x57, 0x02) == 0xAE, "GF(2^8): 57 * 02 = AE");
    check(nhan_gf(&GF256, 0x57, 0x04) == 0x47, "GF(2^8): 57 * 04 = 47");
    check(nhan_gf(&GF256, 0x57, 0x08) == 0x8E, "GF(2^8): 57 * 08 = 8E");
    check(nhan_gf(&GF256, 0x57, 0x10) == 0x07, "GF(2^8): 57 * 10 = 07");

    check(nhan_gf(&GF16, 0x8, 0x2) == 0x3, "GF(2^4): 8 * 2 = 3");
    check(nhan_gf(&GF16, 0x8, 0x8) == 0xC, "GF(2^4): 8 * 8 = C");
    check(nhan_gf(&GF16, 0xB, 0x7) == 0x5, "GF(2^4): B * 7 = 5");
    check(nhan_gf(&GF16, 0x2, 0x9) == 0x1, "GF(2^4): 2 * 9 = 1");
}

static void ss(const truong_gf *t)
{
    uint8_t a, b;
    uint8_t max_val = (uint8_t)((1u << t->n) - 1);
    int ok = 1;
    char name[80];

    for (a = 0; a <= max_val; a++) {
        for (b = 0; b <= max_val; b++) {
            if (nhan_gf(t, a, b) != ref_mul(t, a, b)) {
                ok = 0;
            }
        }
    }
    snprintf(name, sizeof name, "%s: khop cach nhan truyen thong voi moi (a, b)", t->ten);
    check(ok, name);
}

static void tinh_chat(const truong_gf *t)
{
    unsigned a, b, c, size = 1u << t->n;
    unsigned buoc = (t->n == 4) ? 1 : 7;
    int giao_hoan = 1, don_vi = 1, khong = 1, nghich_dao = 1, ket_hop = 1, phan_phoi = 1;
    char name[80];

    for (a = 0; a < size; a++) {
        int co_nghich_dao = 0;

        if (nhan_gf(t, a, 1) != a) don_vi = 0;
        if (nhan_gf(t, a, 0) != 0) khong = 0;
        for (b = 0; b < size; b++) {
            uint16_t ab = nhan_gf(t, a, b);

            if (ab != nhan_gf(t, b, a)) giao_hoan = 0;
            if (ab == 1) co_nghich_dao = 1;
            for (c = 0; c < size; c += buoc) {
                if (nhan_gf(t, ab, c) != nhan_gf(t, a, nhan_gf(t, b, c))) ket_hop = 0;
                if (nhan_gf(t, a, b ^ c) != (ab ^ nhan_gf(t, a, c))) phan_phoi = 0;
            }
        }
        if (a != 0 && !co_nghich_dao) nghich_dao = 0;
    }

    snprintf(name, sizeof name, "%s: a * 1 = a", t->ten);                 check(don_vi, name);
    snprintf(name, sizeof name, "%s: a * 0 = 0", t->ten);                 check(khong, name);
    snprintf(name, sizeof name, "%s: a * b = b * a", t->ten);             check(giao_hoan, name);
    snprintf(name, sizeof name, "%s: (a * b) * c = a * (b * c)", t->ten); check(ket_hop, name);
    snprintf(name, sizeof name, "%s: a * (b + c) = a*b + a*c", t->ten);   check(phan_phoi, name);
    snprintf(name, sizeof name, "%s: moi a khac 0 deu co nghich dao", t->ten); check(nghich_dao, name);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    test_vidu();
    ss(&GF16);
    ss(&GF256);
    tinh_chat(&GF16);
    tinh_chat(&GF256);

    printf("Ket luan: %d PASS, %d FAIL\n", pass, fail);
    return fail == 0 ? 0 : 1;
}