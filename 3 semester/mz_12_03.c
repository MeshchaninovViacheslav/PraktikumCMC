#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>

struct Msg
{
    long msgtype;
    long long x1, x2;
};

int
main(int argc, char *argv[]) {
    int key, n;
    long long value1, value2, maxval;
    sscanf(argv[1], "%d", &key);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lld", &value1);
    sscanf(argv[4], "%lld", &value2);
    sscanf(argv[5], "%lld", &maxval);

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == 0) {
            int num = i + 1;
            struct Msg p;
            while (1) {
                if (msgrcv(msgid, &p, sizeof(p) - sizeof(long), num, 0) == -1) {
                    exit(0);
                }
                long long x3 = p.x1 + p.x2;
                printf("%d %lld\n", num - 1, x3);
                fflush(stdout);
                if (llabs(x3) <= llabs(maxval)) {
                    p.msgtype = x3 % n + 1;
                    p.x1 = p.x2;
                    p.x2 = x3;
                    msgsnd(msgid, &p, sizeof(p) - sizeof(long), 0);
                } else {
                    exit(0);
                }
            }
        } else if (pid == -1) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) != -1);
            exit(1);
        }
    }
    msgsnd(msgid, &(struct Msg) {.msgtype = 1, .x1 =value1, .x2=value2},
           sizeof(struct Msg) - sizeof(long), 0);
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);
    while (wait(NULL) != -1);
    return 0;
}