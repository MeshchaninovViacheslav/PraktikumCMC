#include <iostream>

struct Result {
    long long val;

    Result(long long a) : val(a) {}
};

void Func(long long a, long long b, long long k) {
    if (k == 0) {
        throw Result(a + b);
    } else if (b == 1) {
        throw Result(a);
    } else {
        try {
            Func(a, b - 1, k);
        } catch (Result &exp) {
            Func(a, exp.val, k - 1);
        }
    }
}

int main() {
    long long a, b, k;
    while (std::cin >> a >> b >> k) {
        try {
            Func(a, b, k);
        } catch (Result &exp) {
            std::cout << exp.val << std::endl;
        }
    }

}