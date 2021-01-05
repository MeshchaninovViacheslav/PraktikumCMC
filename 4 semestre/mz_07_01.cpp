#include <iostream>
#include <string>

struct Conv {
    std::string &s;

    Conv(std::string &s_) : s(s_) {}

    ~Conv() {
        std::cout << s << std::endl;
    }
};

void func() {
    std::string s;
    if (std::cin >> s) {
        Conv t(s);
        try {
            func();
        } catch(int a) {
            throw a;
        }
    }
    throw 0;
}

int main() {
    try {
        func();
    } catch (int a) {}
    return 0;
}