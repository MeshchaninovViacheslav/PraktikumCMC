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

using namespace std;

void S();

void A();

void B();

void S() {
    char c;
    cin >> c;
    if (c == 'a') {
        A();
        cin >> c;
        if (c != 'b') {
            throw 1;
        }
    } else if (c == 'c') {
        B();
    } else {
        throw 1;
    }
}

void A() {
    char c;
    cin >> c;
    if (c == 'c') {
        A();
        cin >> c;
        if (c != 'd') {
            throw 1;
        }
    } else if (c != 'e') {
        throw 1;
    }
}

void B() {
    char c;
    if (cin >> c) {
        if (c == 'b') {
            B();
        } else if (c != 'd') {
            throw 1;
        }
    }
}


int main() {
    try {
        S();
        cout << 1 << endl;
    } catch (...) {
        cout << 0 << endl;
    }
    return 0;
}