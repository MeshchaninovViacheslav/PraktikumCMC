#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double mean = 0, disp = 0;
    double a;
    int n = 0;
    while (std::cin >> a) {
        mean += a;
        n++;
        disp += a * a;
    }
    mean /= n;
    disp = std::sqrt((disp / n - mean * mean));
    std::cout << std::setprecision(10) << mean << '\n' << disp << std::endl;
}