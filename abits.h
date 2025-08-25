#ifndef ABITS_TYPE_NAME
#  error "abits.h: ABITS_TYPE_NAME is not defined."
#endif
#ifndef ABITS_LENGTH
#  error "abits.h: ABITS_LENGTH is not defined."
#endif

#include <string.h>     // memset
#include <stdint.h>

#define CAT2(x, y)             x ## y
#define CAT(x, y)              CAT2(x, y)

#define ABITS_NUM_BYTES(nbits)      ( (nbits) / 8 + (((nbits) % 8) ? 1 : 0) )
#define ABITS_TYPE                  CAT(ABITS_TYPE_NAME, _t)
#define ABITS_GET_FUNC              CAT(ABITS_TYPE_NAME, _get_bit)
#define ABITS_ZERO_FUNC             CAT(ABITS_TYPE_NAME, _zero)
#define ABITS_SET_FUNC              CAT(ABITS_TYPE_NAME, _set_bit)
#define ABITS_RST_FUNC              CAT(ABITS_TYPE_NAME, _rst_bit)
#define ABITS_TGL_FUNC              CAT(ABITS_TYPE_NAME, _tgl_bit)
#define ABITS_SET_BITS_FUNC         CAT(ABITS_TYPE_NAME, _set_bits)
#define ABITS_CTZ_FUNC              CAT(ABITS_TYPE_NAME, _ctz)
#define ABITS_COPY_FUNC             CAT(ABITS_TYPE_NAME, _copy)
#define ABITS_IS_ZERO_FUNC          CAT(ABITS_TYPE_NAME, _is_zero)


typedef uint8_t ABITS_TYPE[ABITS_NUM_BYTES(ABITS_LENGTH)];

static inline uint8_t
ABITS_GET_FUNC(ABITS_TYPE ABITS_TYPE_NAME, unsigned int nbit)
{
    return ( ABITS_TYPE_NAME[nbit / 8] >> (nbit % 8) ) & 0x01;
}

static inline void
ABITS_ZERO_FUNC(ABITS_TYPE ABITS_TYPE_NAME)
{
    memset(ABITS_TYPE_NAME, 0x00, sizeof(ABITS_TYPE));
}

static inline void
ABITS_SET_FUNC(ABITS_TYPE ABITS_TYPE_NAME, unsigned int nbit)
{
    ABITS_TYPE_NAME[nbit / 8] |= 1 << (nbit % 8);
}

static inline void
ABITS_RST_FUNC(ABITS_TYPE ABITS_TYPE_NAME, unsigned int nbit)
{
    ABITS_TYPE_NAME[nbit / 8] &= ~( 1 << (nbit % 8) );
}

static inline void
ABITS_TGL_FUNC(ABITS_TYPE ABITS_TYPE_NAME, unsigned int nbit)
{
    ABITS_TYPE_NAME[nbit / 8] ^= 1 << (nbit % 8);
}

static inline void
ABITS_SET_BITS_FUNC(ABITS_TYPE ABITS_TYPE_NAME, unsigned int nbits)
{
    uint8_t nbytes_to_set = nbits / 8;
    memset(ABITS_TYPE_NAME, 0xFF, nbytes_to_set);
    if (nbits % 8) {
        ABITS_TYPE_NAME[nbytes_to_set] |= (1 << (nbits % 8)) - 1;
    }
}

static inline int
ABITS_CTZ_FUNC(ABITS_TYPE ABITS_TYPE_NAME)
{
    for (uint8_t i = 0; i < sizeof(ABITS_TYPE); i++) {
        if (ABITS_TYPE_NAME[i] != 0) {
            int bit = __builtin_ctz(ABITS_TYPE_NAME[i]);
            ABITS_TYPE_NAME[i] ^= 1 << bit;
            return i * 8 + bit;
        }
    }
    return -1;
}

static inline void
ABITS_COPY_FUNC(ABITS_TYPE dst, ABITS_TYPE src)
{
    memcpy(dst, src, sizeof(ABITS_TYPE));
}

static inline int
ABITS_IS_ZERO_FUNC(ABITS_TYPE ABITS_TYPE_NAME)
{
    for (uint8_t i = 0; i < sizeof(ABITS_TYPE); i++) {
        if (ABITS_TYPE_NAME[i] != 0) return 0;
    }
    return 1;
}

