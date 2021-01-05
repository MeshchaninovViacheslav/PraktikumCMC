#include <vector>
#include <cstdint>

void process(const std::vector<uint64_t> &a, std::vector<uint64_t> &b, size_t step) {
    auto it1 = a.begin();
    auto it2 = b.rbegin();
    for (; it1 != a.end() && it2 != b.rend(); it1 = next(it1)) {
        if ((it1 - a.begin()) % step == 0) {
            *it2 += *it1;
            it2 = next(it2);
        }
    }
}