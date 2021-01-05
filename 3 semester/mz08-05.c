#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int pid = fork();
    if (pid == 0) {
        int a, i = 0;
        int status;
        while (scanf("%d", &a) == 1) {
            pid = fork();
            if (pid != 0) {
                wait(&status);
                if (pid < 0 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                    if (i == 0) {
                        printf("-1\n");
                    }
                    exit(1);
                }
                printf("%d\n", a);
                exit(0);
            }
            i++;
        }
    } else if (pid < 0) {
        printf("-1\n");
    } else {
        wait(NULL);
    }
    return 0;
}