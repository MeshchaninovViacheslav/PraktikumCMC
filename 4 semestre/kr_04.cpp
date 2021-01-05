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
#include <assert.h>

using namespace std;

class Figure {
public:
    virtual bool equals(void *) = 0;
};

class Rectangle : public Figure {
    int a, b;
public:
    Rectangle(int a, int b): a(a), b(b) {}
    bool equals(void * r) {
        auto t = (Rectangle *)r;
        if (!t) {
            return 0;
        }
        return t->a == a && t->b == b;
    }
};

class Triangle : public Figure {
    int a, b, c;
public:
    Triangle(int a, int b, int c): a(a), b(b), c(c) {}
    bool equals(void* r) {
        auto t = (Triangle *)r;
        if (!t) {
            return 0;
        }
        return t->a == a && t->b == b && t->c == c;
    }
};

