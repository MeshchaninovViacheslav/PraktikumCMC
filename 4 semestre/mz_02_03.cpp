#include <iostream>
#include <sstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <functional>

namespace numbers {
    complex eval(const std::vector<std::string> &args, const complex &z) {
        complex_stack stack;
        std::map<std::string, std::function<void()>> mp{
                {"z", [&]() { stack = stack << z; }},
                {"+", [&]() {
                    complex tmp = stack[stack.size() - 1] + stack[stack.size() - 2];
                    stack = ~stack;
                    stack = ~stack;
                    stack = stack << tmp;
                }},
                {"-", [&]() {
                    complex tmp = stack[stack.size() - 2] - stack[stack.size() - 1];
                    stack = ~stack;
                    stack = ~stack;
                    stack = stack << tmp;
                }},
                {"*", [&]() {
                    complex tmp = stack[stack.size() - 1] * stack[stack.size() - 2];
                    stack = ~stack;
                    stack = ~stack;
                    stack = stack << tmp;
                }},
                {"/", [&]() {
                    complex tmp = stack[stack.size() - 2] / stack[stack.size() - 1];
                    stack = ~stack;
                    stack = ~stack;
                    stack = stack << tmp;
                }},
                {"!", [&]() {
                    stack = stack << (+stack);
                }},
                {";", [&]() {
                    stack = ~stack;
                }},
                {"~", [&]() {
                    complex tmp = +stack;
                    stack = ~stack;
                    stack = stack << (~tmp);
                }},
                {"#", [&]() {
                    complex tmp = +stack;
                    stack = ~stack;
                    stack = stack << (-tmp);
                }}
        };
        for (auto &op: args) {
            if (op[0] == '(') {
                stack = stack << complex(op);
            } else {
                mp[op]();
            }
        }
        return +stack;
    }
}