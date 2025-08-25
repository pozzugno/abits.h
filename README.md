# What is abits.h

abits.h is a very simple .h file useful when you need to manipulate a very long array of bits (100 or 1000).

# How to use

It's very simple to use:

```
#define ABITS_TYPE_NAME     mybits
#define ABITS_LENGTH        132
#include "abits.h"
```

Now you have `mybits_t` type and a number of useful functions:

```
void mybits_zero(bits_t array)
uint8_t mybits_get_bit(mybits_t array, unsigned int nbit)
void mybits_set_bit(mybits_t array, unsigned int nbit)
void mybits_rst_bit(mybits_t array, unsigned int nbit)
void mybits_tgl_bit(mybits_t array, unsigned int nbit)
void mybits_set_bits(mybits_t array, unsigned int nbits)
int mybits_ctz(mybits_t array)
void mybits_copy(mybits_t dst, mybits_t src)
int mybits_is_zero(mybits_t array)
```

# Example

In the repository there's a test.c that shows an example and makes some tests.

