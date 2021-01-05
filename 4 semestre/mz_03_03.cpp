#include <vector>
#include <cstdint>
#include <algorithm>

void process(const std::vector<int> &v1, std::vector<int> &v2) {
    if (v1.empty() || v2.empty()) {
        return;
    }
    std::vector<int> c = v1;
    std::sort(c.begin(), c.end());
    std::unique(c.begin(), c.end());
    auto it1 = c.begin();
    auto it_ins = v2.begin();
    auto it = v2.begin();
    while (it1 != c.end() && *it1 < 0) {
        it1 = next(it1);
    }
    while (it != v2.end() && it1 != c.end()) {
        if (*it1 == it - v2.begin()) {
            it = next(it);
            it1 = next(it1);
            continue;
        }
        *it_ins = *it;
        it_ins = std::next(it_ins);
        it = std::next(it);
    }
    while (it != v2.end()) {
        *it_ins = *it;
        it_ins = std::next(it_ins);
        it = std::next(it);
    }
    v2.erase(it_ins, v2.end());
}

