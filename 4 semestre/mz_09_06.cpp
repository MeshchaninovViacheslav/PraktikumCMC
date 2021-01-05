#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    struct State {
        std::string state{};
        char term{};
        bool operator<(const State & a) const {
            return std::make_pair(state, term) < std::make_pair(a.state, a.term);
        }
    };

    std::map<State, std::string> data;
    std::vector<std::string> end_states;

    std::string f_state, s_state;
    char term;
    std::cin >> f_state;
    while (f_state != "END") {
        std::cin >> term >> s_state;
        data[{f_state, term}] = s_state;
        std::cin >> f_state;
    }

    std::cin >> f_state;
    while (f_state != "END") {
        end_states.push_back(f_state);
        std::cin >> f_state;
    }

    std::cin >> f_state;
    std::string word;
    std::cin >> word;

    int n{};
    for (auto c: word) {
        auto it = data.find({f_state, c});
        if (it == data.end()) {
            std::cout << 0 << '\n' << n << '\n' << f_state << std::endl;
            return 0;
        }
        n++;
        f_state = it->second;
    }
    if (std::find(end_states.begin(), end_states.end(), f_state) == end_states.end()) {
        std::cout << 0 << '\n' << n << '\n' << f_state << std::endl;

    } else {
        std::cout << 1 << '\n' << n << '\n' << f_state << std::endl;
    }
    return 0;
}