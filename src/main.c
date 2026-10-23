#include <stdio.h>
#include <stdlib.h>
#include "gf.h"

static void mulprint(const truong_gf *t, uint16_t a, uint16_t b)
{
    char dt_a[128], dt_b[128], dt_r[128];
    uint16_t r = nhan_gf(t, a, b);

    da_thuc_string(a, dt_a, sizeof dt_a);
    da_thuc_string(b, dt_b, sizeof dt_b);
    da_thuc_string(r, dt_r, sizeof dt_r);

    printf("Truong %s, m(x) = %s\n", t->ten, t->da_thuc_chu);
    printf("a = %X = %s\n", a, dt_a);
    printf("b = %X = %s\n", b, dt_b);
    printf("a * b = %X = %s\n", r, dt_r);
}

static void xoa_buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int doc_bien(const truong_gf *t, const char *name, uint16_t *ans)
{
    unsigned int max_val = (1u << t->n) - 1;
    unsigned int value;

    printf("Nhap %s (hex, 0 den %X): ", name, max_val);
    if (scanf("%x", &value) != 1) {
        printf("Loi: khong phai so hex\n");
        xoa_buffer();
        return 0;
    }
    if (value > max_val) {
        printf("Loi: %X khong thuoc %s\n", value, t->ten);
        return 0;
    }
    *ans = (uint16_t)value;
    return 1;
}

static void gf16(void)
{
    uint16_t a, b;

    printf("Bang nhan GF(2^4):\n");
    for (a = 0; a < 16; a++) {
        for (b = 0; b < 16; b++) {
            printf("%X ", nhan_gf(&GF16, a, b));
        }
        printf("\n");
    }
}

static int run(void)
{
    int choice, so_doc;
    uint16_t a, b;
    const truong_gf *t;

    for (;;) {
        printf("\nChon (1: GF(2^4), 2: GF(2^8), 3: bang nhan GF(2^4), 0: thoat): ");
        so_doc = scanf("%d", &choice);
        if (so_doc == EOF) {
            return 0;
        }
        if (so_doc != 1) {
            printf("Loi: hay nhap so\n");
            xoa_buffer();
            continue;
        }

        if (choice == 0) {
            return 0;
        } else if (choice == 3) {
            gf16();
            continue;
        } else if (choice == 1) {
            t = &GF16;
        } else if (choice == 2) {
            t = &GF256;
        } else {
            printf("Lua chon khong hop le\n");
            continue;
        }

        if (doc_bien(t, "a", &a) && doc_bien(t, "b", &b)) {
            mulprint(t, a, b);
        }
    }
}

int main(int argc, char *argv[])
{
    const truong_gf *t;
    unsigned long a, b, gioi_han;
    char *het_a, *het_b;

    if (argc == 1) {
        return run();
    }

    if (argc != 4) {
        printf("Cach dung: gfmul <4|8> <a_hex> <b_hex>\n");
        return 1;
    }

    if (argv[1][0] == '4' && argv[1][1] == '\0') {
        t = &GF16;
    } else if (argv[1][0] == '8' && argv[1][1] == '\0') {
        t = &GF256;
    } else {
        printf("Loi: chi ho tro n = 4 hoac 8\n");
        return 1;
    }

    gioi_han = 1ul << t->n;
    a = strtoul(argv[2], &het_a, 16);
    b = strtoul(argv[3], &het_b, 16);
    if (*het_a != '\0' || *het_b != '\0' || a >= gioi_han || b >= gioi_han) {
        printf("Loi: a, b phai la so hex tu 0 den %lX\n", gioi_han - 1);
        return 1;
    }

    mulprint(t, (uint16_t)a, (uint16_t)b);
    return 0;
}