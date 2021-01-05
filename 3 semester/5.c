#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

char *getline2(FILE *);

int
main(void)
{
    enum CONSTANTS
    {
        EMPTY_STR = 0x0bad1dea,
        WRONG_STR = 0xbedabeda
    };
    int num_str = 0;
    char *s = NULL;
    while ((s = getline2(stdin))) {
        num_str++;
        int num_words = 0;
        char *cur_pos = s;
        unsigned int sum_str = 0;
        while (*cur_pos) {
            while (isspace((unsigned char) *cur_pos)) {
                cur_pos++;
            }
            if (!*cur_pos) {
                break;
            }
            if (isdigit((unsigned char) *cur_pos) ||
                ((*cur_pos == '+' || *cur_pos == '-') &&
                 isdigit((unsigned char) cur_pos[1]))) {
                num_words++;
                long n = strtol(cur_pos, &cur_pos, 10);
                if (n > INT_MAX || n < INT_MIN || errno == ERANGE) {
                    n = n > 0 ? num_words : -num_words;
                    errno = 0;
                }
                sum_str += n;
            } else if (!isspace((unsigned char) *cur_pos)) {
                num_words = -1;
                break;
            }
        }
        if (num_words == -1) {
            printf("%d\n", WRONG_STR + num_str);
        } else if (num_words == 0) {
            printf("%d\n", EMPTY_STR + num_str);
        } else {
            printf("%d\n", sum_str);
        }
        free(s);
    }
    return 0;
}