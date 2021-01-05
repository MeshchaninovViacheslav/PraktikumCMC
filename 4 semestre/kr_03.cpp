#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <queue>
#include <list>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>
#include <functional>

using namespace std;

struct Binom {
    uint64_t res;

    Binom(int n, int k) {
        if (n == 0 || k == 0 || n==k) {
            res = 1;
        } else {
            res = Binom(n - 1, k).res + Binom(n - 1, k - 1).res;
        }
    }
};


void calc_binom(int m, int k, std::function<void(uint64_t)> cb) {
    cb(Binom(m, k).res);
}

int main() {
    calc_binom(3, 2, [](uint64_t z) { std::cout << z << std::endl; });
    return 0;
}