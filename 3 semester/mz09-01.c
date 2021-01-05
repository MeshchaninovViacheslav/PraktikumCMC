#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc < 5) {
        return 0;
    }
    pid_t pid = fork();
    if (!pid) {
        int fd0 = open(argv[2], O_RDONLY);
        int fd1 = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fd1 < 0 || fd2 < 0 || fd0 < 0) {
            exit(42);
        }
        if (dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1 || dup2(fd2, 2) == -1) {
            exit(42);
        }

        if (close(fd1) == -1 || close(fd2) == -1 || close(fd0) == -1) {
            exit(42);
        }
        execlp(argv[1], argv[1], NULL);
        exit(42);
    }
    int status;
    wait(&status);
    printf("%d\n", status);
    return 0;
}