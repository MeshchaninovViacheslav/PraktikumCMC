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



namespace Sample{
    template<class T, const size_t n, const size_t m>
    class Matrix {
        class MatrixRow {
            T row[m];
        public:
            const T& operator[](size_t j) const {
                return row[j];
            }
            T& operator[](size_t j) {
                return row[j];
            }
        };

        MatrixRow data[n];

    public:
        const MatrixRow &operator[](size_t i) const {
            return data[i];
        }
        MatrixRow &operator[](size_t i) {
            return data[i];
        }
    };
}
