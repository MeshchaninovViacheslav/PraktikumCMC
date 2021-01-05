#include <iostream>
#include <string>

int main() {
    auto get_symb = [](int a) {
        if (a == '3' || a == '4') {
            return 0;
        } else if (a == '1' || a == '2') {
            return 1;
        }
        return 2;
    };
    std::string s;
    while (std::cin >> s) {
        int state = 0;
        for (size_t i = 0; i < s.length() && state != 2; i++) {
            if (get_symb(s[i]) != state) {
                if (get_symb(s[i]) == 2) {
                    std::cout << 0 << std::endl;
                    state = 2;
                } else if (state == 0) {
                    state = 1;
                } else {
                    std::cout << 0 << std::endl;
                    state = 2;
                }
            }
        }
        if (state != 2) {
            std::cout << 1 << std::endl;
        }
    }
    return 0;
}