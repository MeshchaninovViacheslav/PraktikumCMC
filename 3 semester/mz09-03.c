#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int
check_sucs(char *cmd) {
    // 1  -sucs
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (!pid) {
        execlp(cmd, cmd, NULL);
        exit(1);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[]) {
    return !((check_sucs(argv[1]) || check_sucs(argv[2])) && check_sucs(argv[3]));
}