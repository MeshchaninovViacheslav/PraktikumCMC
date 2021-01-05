//
// Created by vyacheslav on 14.12.2019.
//

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>

int
main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    if (argc == 2) {
        FILE *f1 = fopen(argv[1], "r");
        int a;
        while (fscanf(f1, "%d", &a) == 1) {
            printf("%d ", a);
        }
        printf("\n");
        fflush(stdout);
        fclose(f1);
        return 0;
    }
    FILE *f1 = fopen(argv[1], "r");
    int n = 0, b;
    while (fscanf(f1, "%d", &b) == 1) {
        n++;
    }
    fclose(f1);
    int shmid = shmget(ftok(argv[0], 0), n * sizeof(int), 0666 | IPC_CREAT);
    int *data = shmat(shmid, NULL, 0); // data of first file
    int shmid_el = shmget(ftok(argv[0], 1), n * (argc - 2), 0666 | IPC_CREAT);
    char *elem = shmat(shmid_el, NULL, 0);

    for (int i = 0; i < n * (argc - 2); i++) {
        elem[i] = 0;
    }


    f1 = fopen(argv[1], "r");
    for (int i = 0; fscanf(f1, "%d", &data[i]) == 1; i++);
    fclose(f1);


    for (int i = 2; i < argc; i++) {

        if (fork() == 0) {
            FILE *f = fopen(argv[i], "r");

            int begin = n * (i - 2);
            int j = 0;
            int a;
            int lim = fscanf(f, "%d", &a);
            while (j < n && lim == 1) {
                if (data[j] == a) {
                    j++;
                    lim = fscanf(f, "%d", &a);
                } else {
                    if (data[j] < a) {
                        elem[begin + j] = 1;
                        j++;
                    } else {
                        lim = fscanf(f, "%d", &a);
                    }
                }
            }
            while (j < n) {
                elem[begin + j] = 1;
                j++;
            }

            exit(0);
        }
    }
    while (wait(NULL) != -1);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < argc - 2; i++) {
            elem[j] |= elem[i * n + j];
        }
        if (elem[j] == 0) {
            printf("%d ", data[j]);
        }
    }
    printf("\n");
    fflush(stdout);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid_el, IPC_RMID, NULL);
    return 0;
}