#include <iostream>

void A(int, int);

void B(int);

void S(int);

void S(int n) {
    for (int i = n - 1; i >= 1; i--) {
        std::cout << 'a';
        A(i - 1, n - i);
        std::cout << 'd';
        std::cout << std::endl;
    }
}

void A(int k_a, int k_b) {
    if (k_a > 0) {
        std::cout << 'a';
        A(k_a - 1, k_b);
        std::cout << 'd';
    } else {
        std::cout << 'b';
        B(k_b - 1);
        std::cout << 'c';
    }
}

void B(int k_b) {
    if (k_b > 0) {
        std::cout << 'b';
        B(k_b - 1);
        std::cout << 'c';
    }
}

int main() {
    int n;
    std::cin >> n;
    if (n % 2 == 0 && n >= 4) {
        S(n / 2);
    }
    return 0;
}