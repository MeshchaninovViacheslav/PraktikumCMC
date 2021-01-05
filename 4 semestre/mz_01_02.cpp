#include <iostream>

class A {
private:
    int a;
    bool flag;
public:
    A() : flag(false) {
        std::cin >> a;
    }

    A(const A &t) : flag(true) {
        std::cin >> a;
        a += t.a;
    }

    ~A() {
        if (flag) {
            std::cout << a << std::endl;
        }
    }
};