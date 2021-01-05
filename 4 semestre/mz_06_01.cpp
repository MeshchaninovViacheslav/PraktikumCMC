#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <algorithm>
#include <cmath>

int main() {
    int n{}, m{};
    std::cin >> m >> n;
    int r1{}, r2{}, c1{}, c2{};
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        int y = abs(r1 - r2), x = abs(c1 - c2);
        std::cout << std::min(y, m - y) + std::min(x, n - x) << std::endl;
    }
}