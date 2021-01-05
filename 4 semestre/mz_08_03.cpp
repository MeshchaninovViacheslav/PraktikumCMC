#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    struct Rule {
        std::string key, value;
    };
    auto check_right_key = [](const std::string &s) {
        int state = 0;
        for (auto x: s) {
            if (x >= 'A' && x <= 'Z') {
                state++;
            }
        }
        return (bool) state;
    };

    std::vector<Rule> data;
    Rule t;
    while (std::cin >> t.key >> t.value) {
        data.push_back(t);
    }
    bool Is_S = false;
    bool Is_KS = true;
    bool Is_Non_sh = true;
    for (const auto &x: data) {
        if (!check_right_key(x.key)) {
            std::cout << -1 << std::endl;
            return 0;
        }
        if (x.key == "S") {
            Is_S = true;
        }
        if (x.key.length() != 1) {
            Is_KS = false;
        }
        if (x.key.length() > x.value.length() || (x.key != "S" && x.value == "_")) {
            Is_Non_sh = false;
        }
    }
    if (!Is_S) {
        std::cout << -1 << std::endl;
        return 0;
    }
    if (!Is_KS) {
        std::cout << 10 << std::endl;
        return 0;
    }
    if (!Is_Non_sh) {
        std::cout << 2 << std::endl;
        return 0;
    }
    auto check_value = [](const std::string &s) {
        for (auto x: s) {
            if (x == 'S') {
                return 1;
            }
        }
        return 0;
    };
    bool V_has_S = false, Is_emp = false;
    for (const auto &x: data) {
        if (x.value == "_") {
            Is_emp = true;
        }
        if (check_value(x.value)) {
            V_has_S = true;
        }
    }
    if (V_has_S && Is_emp) {
        std::cout << 2 << std::endl;
    } else {
        std::cout << 23 << std::endl;
    }
    return 0;
}