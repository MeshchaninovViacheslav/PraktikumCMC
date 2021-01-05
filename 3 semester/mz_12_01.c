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
    int npr, key, maxval;
    sscanf(argv[1], "%d", &npr);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &maxval);


    int shmid = shmget(key, sizeof(int) * 2, 0666 | IPC_CREAT);
    if (shmid == -1) {
        return 1;
    }
    int *addr = (int *) shmat(shmid, 0, 0);

    int semid = semget(key, npr, 0666 | IPC_CREAT);
    if (semid == -1) {
        shmdt(addr);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    addr[0] = 0;
    addr[1] = 0;
    semop(semid, &(struct sembuf) {.sem_num = 0, .sem_op = 1, .sem_flg = 0}, 1);

    for (int i = 0; i < npr; i++) {
        if (fork() == 0) {
            while (1) {
                if (semop(semid, &(struct sembuf) {.sem_num = i, .sem_op = -1, .sem_flg = 0}, 1) == -1) {
                    exit(0);
                }
                printf("%d %d %d\n", i + 1, addr[0], addr[1]);
                fflush(stdout);
                long long new = (long long)addr[0] + 1;
                if (new > maxval) {
                    exit(0);
                }
                addr[0] = new;
                addr[1] = i + 1;
                int next =
                        ((unsigned long long) (addr[0] % npr) * (addr[0] % npr) * (addr[0] % npr) * (addr[0] % npr)) %
                        npr;
                semop(semid, &(struct sembuf) {.sem_num = next, .sem_op = 1, .sem_flg = 0}, 1);
            }
        }
    }
    wait(NULL);
    semctl(semid, 0, IPC_RMID, NULL);
    shmdt(addr);
    shmctl(shmid, IPC_RMID, NULL);
    while (wait(NULL) != -1);
    return 0;
}