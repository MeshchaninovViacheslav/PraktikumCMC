#include <iostream>
#include <string>

int main() {
    char c;
    c = std::cin.get();
    while (c != EOF) {
        while(c != EOF && isspace(c)) {
            c = std::cin.get();
        }
        if (c == EOF) {
            break;
        }
        int k = 0, m = 0;
        while(c == '0') {
            k++;
            c = std::cin.get();
        }
        while(c == '1') {
            m++;
            c = std::cin.get();
        }
        int state = 1;
        if (k == 0 || m == 0) {
            std::cout << 0 << '\n';
            state = 0;
        }
        while(c != EOF && !isspace(c) && state) {
            int pat_0 = 0, pat_1 = 0;
            while(c == '0') {
                pat_0++;
                c = std::cin.get();
            }
            while(c == '1') {
                pat_1++;
                c = std::cin.get();
            }
            if (pat_0 != k || pat_1 != m) {
                std::cout << 0 << '\n';
                state = 0;
            }
        }
        if (state == 1) {
            std::cout << 1 << '\n';
        } else {
            while(c != EOF  && !isspace(c)) {
                c = std::cin.get();
            }
        }
    }
    return 0;
}