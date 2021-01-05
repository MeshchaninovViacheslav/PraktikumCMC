#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    enum { BUF_SIZE = 8 };
    int n = 3;
    int num = 0;
    for (int i = 1; i <= n && num == 0; i++) {
        pid_t pid;
        if ((pid = fork()) == 0) {
            num = i;
        }
    }
    if (num == 0) {
        while (wait(NULL) != -1);
    } else {
        char s[BUF_SIZE] = {0};
        read(STDIN_FILENO, s, sizeof(s));
        int d;
        sscanf(s, "%d", &d);
        printf("%d %d\n", num, d * d);
    }
    return 0;
}