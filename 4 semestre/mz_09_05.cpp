#include <iostream>
#include <vector>
#include <queue>


int main() {
    enum {
        NUMBER_NONTERM = 26
    };
    bool state[NUMBER_NONTERM]{};
    std::vector<std::pair<char, std::string>> data;
    std::vector<std::vector<int>> numbers(NUMBER_NONTERM);
    std::string right;
    char left;
    while (std::cin >> left >> right) {
        data.emplace_back(std::make_pair(left, right));
        numbers[left - 'A'].push_back(data.size() - 1);
    }
    std::queue<char> st({'S'});

    while (!st.empty()) {
        char c = st.front();
        st.pop();
        state[c - 'A'] = true;
        for (auto n: numbers[c - 'A']) {
            for (auto t: data[n].second) {
                if (t >= 'A' && t <= 'Z' && !state[t - 'A']) {
                    st.push(t);
                }
            }
        }
    }

    for (auto &v: data) {
        if (state[v.first - 'A']) {
            std::cout << v.first << " " << v.second << '\n';
        }
    }
    return 0;
}