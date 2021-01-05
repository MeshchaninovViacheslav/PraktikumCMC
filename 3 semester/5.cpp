#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int pfd1[2];
    pipe(pfd1);
    if(fork() == 0){
        close(pfd1[0]);
        int fd = open(argv[4], O_RDONLY);
        dup2(fd, 0);
        close(fd);
        dup2(pfd1[1], 1);
        close(pfd1[1]);
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    if(fork() == 0){
        close(pfd1[1]);
        dup2(pfd1[0], 0);
        close(pfd1[0]);
        int fd = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0640);
        dup2(fd, 1);
        close(fd);
        if(fork() == 0){
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        int status;
        wait(&status);
        if (!(WIFEXITED(status) == 0 || WEXITSTATUS(status) != 0)) {
            exit(0);
        }
        if(fork() == 0){
            execlp(argv[3], argv[3], NULL);
            exit(1);
        }
        wait(NULL);
    }
    while(wait(NULL) != -1);
    return 0;
}