#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

volatile int num_sigint = 0;
volatile int p = 0;

void handler(int sgn) {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    if (sgn == SIGTERM) {
        exit(0);
    }
    if (num_sigint == 3) {
        exit(0);
    }
    num_sigint++;
    printf("%d\n", p);
    fflush(stdout);
}

int IsPrime(int n)
{
    if (n == 1 || n == 0) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    printf("%d\n", getpid());
    fflush(stdout);

    int low, high;
    scanf("%d%d", &low, &high);

    for (int i = low; i < high; i++){
        if (IsPrime(i) == 1) {
            p = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}