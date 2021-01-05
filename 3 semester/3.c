#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int pfd[2];
    int r_pfd[2];
    pipe(pfd);
    pipe(r_pfd);
    if (fork() == 0) {
        close(r_pfd[0]);
        if (fork() == 0) {
            close(pfd[1]);
            double a, res = 0;
            int n = 0;
            while (read(pfd[0], &a, sizeof(a)) == sizeof(a)) {
                res += a;
                n++;
            }
            if (n != 0) {
                write(r_pfd[1], &res, sizeof(res));
            }
            close(r_pfd[1]);
            close(pfd[0]);
            exit(0);
        }
        close(pfd[0]);
        close(r_pfd[1]);
        FILE *f = fopen(argv[1], "r");
        double a;
        while (fscanf(f, "%lf", &a) == 1) {
            if (a >= 0) {
                write(pfd[1], &a, sizeof(a));
            }
        }
        close(pfd[1]);
        return 0;
    }
    close(pfd[0]);
    close(pfd[1]);
    close(r_pfd[1]);
    double res;
    if(read(r_pfd[0], &res, sizeof(res)) == sizeof(res)){
        printf("%.10lf\n", res);
    }
    close(r_pfd[0]);
    return 0;
}