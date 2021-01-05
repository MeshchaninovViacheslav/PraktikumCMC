#include <stdio.h>
#include <limits.h>
#include <string.h>

enum Sizes
{
    S_SIZE = PATH_MAX + 3,
    A_SIZE = 10
};

int
main(void)
{
    long long a[A_SIZE] = {};
    char name_file[S_SIZE];
    if (fgets(name_file, sizeof(name_file), stdin)) {
        int len = strlen(name_file);
        while (len > 0 && (name_file[len - 1] == '\n' ||
                           name_file[len - 1] == '\r')) {
            len--;
            name_file[len] = 0;
        }
        FILE *f = fopen(name_file, "r");
        if (f) {
            int c;
            while ((c = getc_unlocked(f)) != EOF) {
                if (c >= '0' && c <= '9') {
                    a[c - '0']++;
                }
            }
            fclose(f);
        }
    }
    for (int i = 0; i < A_SIZE; i++) {
        printf("%d %lld\n", i, a[i]);
    }
}