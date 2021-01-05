#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum CONST
{
    FULL_PR = 100,
    ROUND_C = 10000
};

double
round_double(double a)
{
    return round(a * ROUND_C) * 1.0 / ROUND_C;
}

int
main(int argc, char *argv[])
{
    char *s;
    double cource = strtod(argv[1], &s);
    for(int i = 2; i < argc; i++){
        double per = strtod(argv[i], &s);
        cource += cource * (per / FULL_PR);
        cource = round_double(cource);
    }
    cource = round_double(cource);
    printf("%.4f\n", cource);
    return 0;
}