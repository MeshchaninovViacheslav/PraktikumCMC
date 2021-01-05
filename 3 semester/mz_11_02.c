#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

volatile int mode = 0;
// 0 - add, 1 - mul

void handler(int sgn) {
    signal(SIGQUIT, handler);
    signal(SIGINT, handler);

    if (sgn == SIGINT) {
        mode = 0;
    } else if (sgn == SIGQUIT) {
        mode = 1;
    }
}


int main(int argc, char *argv[]) {
    signal(SIGQUIT, handler);
    signal(SIGINT, handler);

    printf("%d\n", getpid());
    fflush(stdout);

    int a;
    unsigned int res = 0;
    while(scanf("%d", &a) == 1){
        if (mode == 0) {
            res += a;
        } else {
            res *= a;
        }
        printf("%d\n", res);
        fflush(stdout);
    }
}