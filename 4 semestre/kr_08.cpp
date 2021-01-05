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

std::string gen_power(uint32_t power) {
    if (power == 0) {
        return "1";
    }
    std::string s;
    for (uint32_t i = 0; i< power;i++) {
        s.push_back('x');
    }
    for (uint32_t i = 1; i< power;i++) {
        s.push_back('*');
    }
    return s;
}
