#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int
main(void)
{
    long long a, b;
    scanf("%lld%lld", &a, &b);
    long long c = b * (a / b);
    if (a > 0) {
        if (a - c >= c + b - a) {
            c += b;
        }
        if (c > INT_MAX) {
            c -= b;
        }
    } else {
        if (c - a > a + b - c) {
            c -= b;
        }
        if (c < INT_MIN) {
            c += b;
        }
    }
    printf("%lld\n", c);
    return 0;
}