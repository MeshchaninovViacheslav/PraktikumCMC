#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/wait.h>

void
operation(int *, int, int, int);

enum
{
    RAND_C = 10
};

int
main(int argc, char *argv[])
{
    int count, key, nproc, iter_count;
    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &nproc);
    sscanf(argv[4], "%d", &iter_count);

    int shmid = shmget(key, count * sizeof(int), 0666 | IPC_CREAT);
    int *data = shmat(shmid, NULL, 0);

    int semid = semget(key, count, 0666 | IPC_CREAT);
    for (int i = 0; i < count; i++) {
        semctl(semid, i, SETVAL, (int) 1);
        scanf("%d", &data[i]);
    }

    for (int i = 0; i < nproc; i++) {
        if (fork() == 0) {
            unsigned int seed;
            sscanf(argv[i], "%u", &seed);
            srand(seed);
            for (int j = 0; j < iter_count; j++) {
                int ind1 = rand() % count, ind2 = rand() % count, val = rand() % RAND_C;
                struct sembuf sem[2];
                sem[0] = (struct sembuf) {.sem_num=ind1, .sem_op=-1, .sem_flg=0};
                sem[1] = (struct sembuf) {.sem_num=ind2, .sem_op=-1, .sem_flg=0};
                if (ind1 != ind2) {
                    semop(semid, sem, 2);
                    operation(data, ind1, ind2, val);
                    sem[0].sem_op = 1;
                    sem[1].sem_op = 1;
                    semop(semid, sem, 2);
                }
            }
            exit(0);
        }
    }
    while (wait(NULL) != -1);
    for (int i = 0; i < count; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    fflush(stdout);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, 0);
    return 0;
}