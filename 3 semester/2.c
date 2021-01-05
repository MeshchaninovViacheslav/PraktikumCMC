#include <stdio.h>

int
main(int argc, char *argv[])
{
    long long sum_p = 0, sum_n = 0;
    for(int i = 1; i < argc; i++){
        int a;
        sscanf(argv[i], "%d", &a);
        if(a > 0) {
            sum_p += a;
        } else {
            sum_n += a;
        }
    }
    printf("%lld\n%lld\n", sum_p, sum_n);
    return 0;
}