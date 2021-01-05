#include <stdint.h>

enum
{
    I_MIN = ~(~0u >> 1),
    I_MAX = ~0u >> 1
};

int32_t
satsum(int32_t v1, int32_t v2)
{
    int res;
    if (!__builtin_sadd_overflow(v1, v2, &res)) {
        return res;
    }
    if (v1 > 0) {
        return I_MAX;
    }
    return I_MIN;
}