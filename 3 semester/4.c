#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int
main(void)
{
    enum
    {
        BUFF_SIZE = 16
    };
    unsigned long long sum = 0;
    ssize_t n = 0;
    unsigned char buf[BUFF_SIZE];
    int sign = 1;
    unsigned long long cur_num = 0;
    while ((n = read(STDIN_FILENO, &buf, sizeof(buf))) > 0) {
        int it = 0;
        if (isspace(buf[it])) {
            sum += cur_num;
            cur_num = 0;
            sign = 1;
        }
        while (it < n) {
            if (isspace(buf[it])) {
                sum += cur_num;
                cur_num = 0;
                sign = 1;
                it++;
            } else if (buf[it] == '+') {
                it++;
            } else if (buf[it] == '-') {
                sign = -1;
                it++;
            } else {
                cur_num = cur_num * 10 + sign * (buf[it] - '0');
                it++;
            }
        }
    }
    sum += cur_num;
    if (n < 0) {
        return 1;
    }
    printf("%lld\n", sum);
    return 0;
}