#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int num_sgn = 0;

enum
{
    MAX_SGN = 5
};

void handler(int sgn){
    signal(SIGHUP, handler);
    if (num_sgn == MAX_SGN) {
        exit(0);
    }
    printf("%d\n", num_sgn);
    fflush(stdout);
    num_sgn++;
}

int main(int argc, char *argv[]) {
    signal(SIGHUP, handler);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1){
        pause();
    }
    return 0;
}