#include <iostream>
#include <sstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include "../cmc_complex.h"
#include <cstring>
#include <memory>
#include "../cmc_complex_stack.h"
#include "../cmc_complex_eval.h"

int main(int argc, char **argv) {
    std::vector<std::string> v;
    for (int i = 4; i < argc; i++) {
        v.emplace_back(argv[i]);
    }
    numbers::complex c(argv[1]);
    std::stringstream ss(argv[2]);
    double r;
    ss >> r;
    int n = std::stoi(argv[3]);
    numbers::complex square{};
    double alpha = 0;
    double d = 2 * M_PI / n;
    int i = 0;
    while (i < n) {
        numbers::complex t{r * cos(alpha + d / 2), r * sin(alpha + d / 2)};
        t = t + c;
        numbers::complex b = c + numbers::complex{r * cos(alpha + d), r * sin(alpha + d)};
        numbers::complex a = c + numbers::complex{r * cos(alpha), r * sin(alpha)};
        square += numbers::eval(v, t) * (b - a);
        alpha += d;
        ++i;
    }
    std::cout << square.to_string();
    return 0;
}