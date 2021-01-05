#include <vector>
#include <cstdint>
#include <algorithm>

template <class IT_N, class IT_EL>
auto myremove(IT_N begin1, IT_N end1, IT_EL begin2, IT_EL end2) {
    std::vector<typename IT_N::value_type> c(begin1, end1);
    std::sort(c.begin(), c.end());
    std::unique(c.begin(), c.end());

    auto it1 = c.begin();
    auto it_ins = begin2;
    auto it = begin2;
    while (it1 != c.end() && *it1 < 0) {
        it1 = next(it1);
    }
    while (it != end2 && it1 != c.end()) {
        if (*it1 == it - begin2) {
            it = next(it);
            it1 = next(it1);
            continue;
        }
        *it_ins = std::move(*it);
        it_ins = std::next(it_ins);
        it = std::next(it);
    }
    while (it != end2) {
        *it_ins = std::move(*it);
        it_ins = std::next(it_ins);
        it = std::next(it);
    }
    return it_ins;
}