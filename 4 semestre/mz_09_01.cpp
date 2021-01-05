#include <iostream>

// grammar type is 0, language type is 0, language is a^n 0^m b^n 1^m

int main() {
    std::string s;
    while (std::cin >> s) {
        int n = 0, m = 0;
        auto it = s.begin();
        while (it != s.end() && *it == 'a') {
            ++it;
        }
        n = it - s.begin();
        while (it != s.end() && *it == '0') {
            ++it;
        }
        m = it - s.begin();
        m -= n;
        if (n != 0 && m != 0) {
            while (it != s.end() && *it == 'b') {
                ++it;
                n--;
            }
            while (it != s.end() && *it == '1') {
                ++it;
                m--;
            }
            if (it == s.end() && m == 0 && n == 0) {
                std::cout << 1 << std::endl;
            } else {
                std::cout << 0 << std::endl;
            }
        } else {
            std::cout << 0 << std::endl;
        }
    }
}