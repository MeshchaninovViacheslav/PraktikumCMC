#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int
mysys(const char *str)
{
    enum { SIG = 128 };
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(SIG - 1);
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) != 0) {
        return SIG + WTERMSIG(status);
    }
    return WEXITSTATUS(status);
}