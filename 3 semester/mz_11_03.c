#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n;
    sscanf(argv[1], "%d", &n);
    for (int i = 0; i < n && i < argc - 2; i++) {
        char name[PATH_MAX + 1] = {0};
        FILE *f = fopen(argv[i + 2], "r");
        fgets(name, PATH_MAX + 1, f);
        fclose(f);
        name[strlen(name) - 1] = 0;
        if (fork() == 0) {
            execlp(name, name, NULL);
            exit(1);
        }
    }
    int res = 0;
    int status;
    while (wait(&status) != -1) {
        if (!(WIFEXITED(status) == 0 || WEXITSTATUS(status) != 0)) {
            res++;
        }
    }
    for (int i = n + 2; i < argc; i++) {
        char name[PATH_MAX + 1] = {0};
        FILE *f = fopen(argv[i], "r");
        fgets(name, PATH_MAX + 1, f);
        fclose(f);
        name[strlen(name) - 1] = 0;
        if (fork() == 0) {
            execlp(name, name, NULL);
            exit(1);
        }
        if (wait(&status) != -1) {
            if (!(WIFEXITED(status) == 0 || WEXITSTATUS(status) != 0)) {
                res++;
            }
        }
    }
    printf("%d\n", res);
    fflush(stdout);
    return 0;
}