#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int *pids = calloc(argc - 1, sizeof(*pids));
    for(int i = 1; i < argc; i++){
        long long a;
        sscanf(argv[i], "%lld", &a);
        unsigned long long t = a;
        if((pids[i - 1] = fork()) == 0){
            int res = 0;
            while(t != 0){
                res += (t&1);
                t >>= 1;
            }
            exit(res);
        }
    }
    int pid;
    int status;
    int *res = calloc(argc - 1, sizeof(*res));
    while((pid = wait(&status)) != -1){
        int i = 0;
        while(pids[i] != pid){
            i++;
        }
        res[i] = WEXITSTATUS(status);
    }
    for(int i = 0; i < argc - 1; i++){
        printf("%d\n", res[i]);
    }
    free(pids);
    free(res);
    return 0;
}