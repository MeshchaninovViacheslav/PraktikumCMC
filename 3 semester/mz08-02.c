#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    int n = 3;
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            printf("%d", i);
        } else {
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
                printf(" %d", i);
                if (i == 1) {
                    printf("\n");
                }
                i = n;
            }
        }
    }
    return 0;
}