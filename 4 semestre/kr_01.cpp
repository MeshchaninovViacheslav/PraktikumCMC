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
#include <numeric>

using namespace std;

void process(vector<uint64_t > &v, uint32_t s) {
    if (v.empty()) {
        return;
    }
    uint32_t n = v.size() / s;
    v.resize(v.size() + n);
    uint64_t sum = 0;
    for (auto x: v) {
        sum += x;
    }
    auto itr = v.size() - 1, itl = v.size() - n - 1;
    while(itr >= s) {
        if ((itl + 1) % s != 0) {
            v[itr] = v[itl];
        } else {
            v[itr] = sum;
            itr--;
            v[itr] = v[itl];
        }
        sum -= v[itl];
        if (itl == 0) {
            break;
        }
        itr--;
        itl--;
    }
}
