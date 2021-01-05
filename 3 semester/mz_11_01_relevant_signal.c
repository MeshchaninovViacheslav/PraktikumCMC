#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int num_sgn = 0;

enum
{
    MAX_SGN = 5
};

void
handler(int signal)
{
    if (num_sgn == MAX_SGN) {
        exit(0);
    }
    printf("%d\n", num_sgn);
    fflush(stdout);
    num_sgn++;
}

int main(int argc, char *argv[])
{
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL); // FIXME
    printf("%d\n", getppid());
    fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}