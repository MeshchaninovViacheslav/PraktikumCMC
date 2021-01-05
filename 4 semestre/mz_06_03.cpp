#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <algorithm>
#include <cmath>

namespace Game {
    template<typename T>
    class Coord {
    public:
        T row, col;

        Coord(T x = {}, T y = {}) : row(x), col(y) {}

        typedef T value_type;
    };

    template<typename T>
    T dist(const Coord<T> &size, const Coord<T> &a, const Coord<T> &b) {
        T y = a.row - b.row, x = abs(a.col - b.col);
        T r = x / 2;
        if ((a.col % 2 == 1 && y > 0) || (a.col % 2 == 0 && y < 0)) {
            r += (x % 2);
        }
        y = abs(y);
        if (r < y) {
            return x + y - r;
        }
        return x;
    }
}