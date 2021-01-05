#include <vector>
#include <cstdint>
#include <iostream>

void process(std::vector<int64_t> &a, int64_t thr) {
    size_t new_sz = a.size();
    for (auto x: a) {
        if (x >= thr) {
            new_sz++;
        }
    }
    a.reserve(new_sz);
    for (auto it = a.rbegin(); it != a.rend(); it++) {
        if (*it >= thr) {
            a.push_back(*it);
        }
    }
}