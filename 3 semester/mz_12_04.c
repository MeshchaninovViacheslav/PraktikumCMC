#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setvbuf(stdin, NULL, _IONBF, 0);
    int count;
    sscanf(argv[1], "%d", &count);
    key_t key = ftok(argv[0], 0);
    int semid = semget(key, count, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid == -1) {
        return 1;
    }
    semop(semid, &(struct sembuf) {.sem_num=0, .sem_op=1, .sem_flg=SEM_UNDO}, 1);
    for (int i = 0; i < count; i++) {
        if (fork() == 0) {
            while (1) {
                if (semop(semid, &(struct sembuf) {.sem_num=i, .sem_op=-1, .sem_flg=SEM_UNDO}, 1) == -1) {
                    return 0;
                }
                int a;
                if (scanf("%d", &a) != 1) {
                    return 0;
                }
                printf("%d %d\n", i, a);
                fflush(stdout);
                int next = (a % count + count) % count;

                semop(semid, &(struct sembuf) {.sem_num=next, .sem_op=1, .sem_flg=SEM_UNDO}, 1);
            }
        }
    }
    wait(NULL);
    semctl(semid, 0, IPC_RMID, NULL);
    while (wait(NULL) != -1);
    return 0;
}