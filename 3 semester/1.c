#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

void dfs(int n, int deep, int max_deep){
    if(deep > max_deep){
        return;
    }
    if(fork() == 0){
        dfs(2 * n + 1, deep + 1, max_deep);
        exit(0);
    }
    wait(NULL);
    printf("%d\n", n);
    fflush(stdout);
    if(fork() == 0){
        dfs(2 * n + 2, deep + 1, max_deep);
        exit(0);
    }
    wait(NULL);
    return;
}


int main(int argc, char *argv[]) {
    int n;
    sscanf(argv[1], "%d", &n);
    dfs(0, 0, n);
    return 0;
}