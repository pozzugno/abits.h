/* Incomplete tests */
#include <stdio.h>
#include <assert.h>

#define ABITS_TYPE_NAME     arr_s
#define ABITS_LENGTH        4
#include "abits.h"

#undef ABITS_TYPE_NAME
#undef ABITS_LENGTH
#define ABITS_TYPE_NAME     arr_l
#define ABITS_LENGTH         80
#include "abits.h"

void
print_arr_s(arr_s_t a)
{
    for (int i = 3; i >= 0; i--) {
        printf("%d", arr_s_get_bit(a, i));
    }
}

void
assert_s(arr_s_t a, unsigned long int value)
{
    unsigned long int num = value;
    for (int i = 0; i < 4; i++, num >>= 1) {
        if (arr_s_get_bit(a, i) != (num & 0x01)) {
            printf("assert_s failed on bit %d\n", i);
            printf("array: ");
            print_arr_s(a);
            printf(" - expected value: %lx\n", value);
        }
    }
}

void
print_arr_l(arr_l_t a)
{
    uint8_t cnt = 0;
    for (int i = 79; i >= 0; i--) {
        printf("%d", arr_l_get_bit(a, i));
        if (++cnt == 4) {
            printf("|");
            cnt = 0;
        }
    }
}

void
assert_l(arr_l_t a, unsigned long int high, unsigned long int low)
{
    unsigned int long num = low;

    for (int i = 0; i < 79; i++) {
        if (arr_l_get_bit(a, i) != (num & 0x01)) {
            printf("assert_l failed on bit %d\n", i);
            printf("array: ");
            print_arr_l(a);
            printf(" - expected value: 0x%016lx%016lx\n", high, low);
            assert(0);
        }
        if (i == 63) {
            num = high;
        } else {
            num >>= 1;
        }
    }
}

int
main(void)
{
    arr_s_t arr_s;
    arr_l_t arr_l;

    arr_s_zero(arr_s);
    assert_s(arr_s, 0x00);
    arr_s_set_bit(arr_s, 0);    
    assert_s(arr_s, 0x01);
    arr_s_set_bits(arr_s, 3);
    assert_s(arr_s, 0x07); 
    arr_s_tgl_bit(arr_s, 1);
    assert_s(arr_s, 0x05);

    arr_l_zero(arr_l);
    assert_l(arr_l, 0x0000000000000000, 0x0000000000000000);
    arr_l_set_bit(arr_l, 66);    
    assert_l(arr_l, 0x0000000000000004, 0x0000000000000000);
    arr_l_set_bits(arr_l, 62);
    assert_l(arr_l, 0x0000000000000004, 0x3FFFFFFFFFFFFFFF); 
    arr_l_tgl_bit(arr_l, 1);
    assert_l(arr_l, 0x0000000000000004, 0x3FFFFFFFFFFFFFFD); 
    arr_l_rst_bit(arr_l, 0);
    arr_l_rst_bit(arr_l, 2);
    arr_l_rst_bit(arr_l, 3);
    assert_l(arr_l, 0x0000000000000004, 0x3FFFFFFFFFFFFFF0); 
    assert(arr_l_ctz(arr_l) == 4); 



    return 0;
}
