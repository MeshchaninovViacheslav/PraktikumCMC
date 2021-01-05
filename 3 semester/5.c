#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum
{
    BATCH_SIZE = 9,
    BUFF_SIZE = 50000 / 9 + 1,
    GR_SIZE = 32,
    BATCH_M = (int) 1e9
};

unsigned
mul_2(unsigned *a, int n)
{
    unsigned long long c = 1LLU << GR_SIZE;
    unsigned long long r = 0;
    for (int i = n - 1; i >= 0; --i) {
        unsigned long long tmp = a[i] * c + r;
        a[i] = tmp % BATCH_M;
        r = tmp / BATCH_M;
    }
    return r;
}

unsigned
add_ar(unsigned *a, int n, unsigned long long t)
{
    unsigned long long c = 1LLU << GR_SIZE;
    unsigned long long r = t;
    for (int i = n - 1; i >= 0; --i) {
        unsigned long long tmp = a[i] + r;
        a[i] = tmp % c;
        r = tmp / c;
    }
    return r;
}

void
print_ar(unsigned *a, int size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%.8x ", a[i]);
    }
    printf("\n");
}


int
main(void)
{
    int prec;
    scanf("%d ", &prec);
    int res_size = prec / GR_SIZE + 1;
    unsigned *buf = calloc(BUFF_SIZE, sizeof(*buf));
    unsigned *res = calloc(res_size, sizeof(*res));
    if (!buf || !res) {
        exit(1);
    }
    int flag_ex = 0;
    if (prec % GR_SIZE == 0) {
        flag_ex = 1;
    }
    int c = 0;
    int len = 0;
    while((c = getchar()) != EOF && isdigit(c)){
        buf[len / BATCH_SIZE] = buf[len / BATCH_SIZE] * 10 + c - '0';
        len++;
    }
    while(len % BATCH_SIZE != 0) {
        buf[len / BATCH_SIZE] *= 10;
        len++;
    }
    int size = len / BATCH_SIZE;

    for (int i = 0; i < res_size; i++) {
        res[i] = mul_2(buf, size);
    }

    unsigned r = 0;
    if (flag_ex) {
        unsigned first_bit = (res[res_size - 1] >> (GR_SIZE - 1)) & 1;
        if (first_bit) {
            unsigned flag_half = (res[res_size - 1] & ~(1U << (GR_SIZE - 1)));
            for (int i = 0; i < size; i++) {
                if (buf[i] != 0) {
                    flag_half = 1;
                }
            }
            if (flag_half != 0) {
                r = add_ar(res, res_size - 1, 1);
            } else {
                unsigned bit2 = res[res_size - 2] & 1;
                if (bit2 == 1) {
                    r = add_ar(res, res_size - 1, 1);
                }
            }
        }
    } else {
        unsigned pos = prec % GR_SIZE;
        unsigned bit1 = (res[res_size - 1] >> (GR_SIZE - pos)) & 1;
        unsigned bit2 = (res[res_size - 1] >> (GR_SIZE - pos - 1)) & 1;
        if (bit2 == 1) {
            unsigned flag_nhalf = 0;
            if (pos != GR_SIZE - 1) {
                unsigned tmp = res[res_size - 1] & ((1U << (GR_SIZE - pos - 1)) - 1);
                if (tmp != 0) {
                    flag_nhalf = 1;
                }
            }
            for (int i = 0; i < size; i++) {
                if (buf[i] != 0) {
                    flag_nhalf = 1;
                }
            }
            if (flag_nhalf == 1 || bit1) {
                r = add_ar(res, res_size, 1U << (GR_SIZE - pos));
            }
        }
        res[res_size - 1] = res[res_size - 1] & ~((1U << (GR_SIZE - pos)) - 1);
    }
    if (flag_ex) {
        res_size--;
    }
    if (r) {
        printf("%d ", r);
    }
    print_ar(res, res_size);
    free(res);
    free(buf);
    return 0;
}