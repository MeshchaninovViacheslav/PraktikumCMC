#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <algorithm>

int main() {
    std::map<std::string, std::function<Figure *(const std::string &)>> mp{
            {"R", [](const std::string &s) -> Figure * {
                std::stringstream ss(s);
                std::string name{}, a{}, b{};
                ss >> name >> a >> b;

                return Rectangle::make(a + " " + b);
            }},
            {"S", [](const std::string &s) -> Figure * {
                std::stringstream ss(s);
                std::string name{}, a{};
                ss >> name >> a;
                return Square::make(a);
            }},
            {"C", [](const std::string &s) -> Figure * {
                std::stringstream ss(s);
                std::string name{}, a{};
                ss >> name >> a;
                return Circle::make(a);
            }}
    };
    std::vector<std::unique_ptr<Figure>> v;
    std::string s;
    while (std::getline(std::cin, s)) {
        std::stringstream ss(s);
        std::string name;
        ss >> name;
        v.emplace_back(mp[name](ss.str()));
    }
    std::stable_sort(v.begin(), v.end(), [](auto &a, auto &b) {
        return a->get_square() < b->get_square();
    });
    for (auto &x: v) {
        std::cout << x->to_string() << std::endl;
    }
    return 0;
}