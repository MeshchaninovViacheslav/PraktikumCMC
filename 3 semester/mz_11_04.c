#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

FILE *f_r, *f_w;
volatile int max_sgn;
volatile int id;

void handler(int sgn) {
    signal(SIGUSR1, handler);
    int a, pid;
    fscanf(f_r, "%d %d", &pid, &a);
    if (a == max_sgn){
        fprintf(f_w, "%d %d\n", getpid(), a);
        fflush(f_w);
        kill(pid, SIGUSR1);
        fclose(f_r);
        fclose(f_w);
        exit(0);
    }
    printf("%d %d\n", id, a);
    fflush(stdout);
    a++;
    fprintf(f_w, "%d %d\n", getpid(), a);
    fflush(f_w);
    kill(pid, SIGUSR1);
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, handler);

    int fd[2];
    pipe(fd);

    sscanf(argv[1], "%d", &max_sgn);

    f_r = fdopen(fd[0], "r");
    f_w = fdopen(fd[1], "w");

    int pid1 = fork();
    if (pid1 == 0) {
        id = 1;
        while (1) {
            pause();
        }
    }

    int pid2 = fork();
    if (pid2 == 0) {
        id = 2;
        while (1) {
            pause();
        }
    }

    fprintf(f_w, "%d %d\n", pid2, 1);
    fflush(f_w);
    kill(pid1, SIGUSR1);

    fclose(f_r);
    fclose(f_w);

    while(wait(NULL) != -1);
    printf("Done\n");
    fflush(stdout);
    return 0;
}