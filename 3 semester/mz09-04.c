#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>


int
main(int argc, char *argv[]) {
    char tmp[] = "/tmp";
    char *dir = getenv("XDG_RUNTIME_DIR");
    if (!dir) {
        dir = getenv("TMPDIR");
    }
    if (!dir) {
        dir = tmp;
    }
    char filename1[PATH_MAX] = {0};
    snprintf(filename1, sizeof(filename1), "%s/file%d", dir, getpid());
    int fd1 = open(filename1, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    write(fd1, "print(", strlen("print("));
    for (int i = 1; i < argc - 1; i++) {
        write(fd1, argv[i], strlen(argv[i]));
        write(fd1, "*", strlen("*"));
    }
    write(fd1, argv[argc - 1], strlen(argv[argc - 1]));
    write(fd1, ")", strlen(")"));
    close(fd1);

    char filename2[PATH_MAX] = {0};
    snprintf(filename2, sizeof(filename2), "%s/com%d", dir, getpid());
    char s[4 * PATH_MAX] = {0};
    snprintf(s, sizeof(s), "#! /bin/bash\npython %s\nrm %s\n rm %s\n", filename1, filename1, filename2);
    int fd2 = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    write(fd2, s, sizeof(s));
    close(fd2);
    execlp("/bin/sh", "sh", filename2, NULL);
    return 0;
}