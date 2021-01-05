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

template<typename T>
class Coord{
public:
    T row, col;
    Coord(T x = {}, T y = {}): row(x), col(y){}
    typedef T value_type;
};

template <typename T>
T dist(const Coord<T>& size, const Coord<T> &a, const Coord<T> & b) {
    T y = abs(a.row - b.row), x = abs(a.col - b.col);
    T path_y = std::min(y, size.row - y), path_x = std::min(x, size.col - x);
    return std::max(path_y, path_x);
}