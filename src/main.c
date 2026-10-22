#include <stdio.h>
#include "gf.h"

int main(void)
{
    printf("%s: 0x57 * 0x83 = 0x%02X  (res: 0xC1)\n",
           GF256.name, gf_mul(&GF256, 0x57, 0x83));
    printf("%s: 0x8  * 0x2  = 0x%X  (res: 0x3)\n",
           GF16.name, gf_mul(&GF16, 0x8, 0x2));
    return 0;
}