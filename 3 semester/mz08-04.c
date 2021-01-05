#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            printf(" %d\n", i);
            fflush(stdout);
            break;
        } else {
            if (i == 1) {
                printf("%d", i);
                fflush(stdout);
            } else {
                printf(" %d", i);
                fflush(stdout);
            }
            pid_t pid;
            if ((pid = fork()) < 0) {
                perror("fork");
                exit(1);
            } else if (pid) {
                int status;
                wait(&status);
                if (!WIFEXITED(status) || WEXITSTATUS(status)) {
                    exit(1);
                }
                i = n;
                break;
            }
        }
    }
    return 0;
}