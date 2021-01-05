#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Sum {
public:
    double s = 0;

    void operator()(double x) {
        s += x;
    }
};

int main() {
    std::vector<double> a;
    double x;
    while (std::cin >> x) {
        a.push_back(x);
    }
    int f_10 = a.size() / 10;
    a.erase(a.begin(), a.begin() + f_10);
    a.erase(a.end() - f_10, a.end());
    std::sort(a.begin(), a.end());
    auto l = a.begin(), r = a.end();
    int s_10 = a.size() / 10;
    l += s_10;
    r -= s_10;
    Sum t = std::for_each(l, r, Sum());
    std::cout << std::setprecision(10) << std::fixed << t.s / (r - l);
}