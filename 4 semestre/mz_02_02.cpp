#include <iostream>
#include <sstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include <cstring>

namespace numbers {
    class complex_stack {
    private:
        complex *data = new complex[64];
        size_t sz = 0, capacity = 64;

        void increase() {
            complex *data_new = new complex[capacity * 2];
            memcpy(data_new, data, capacity);
            delete[] data;
            capacity *= 2;
        }

        void move_(complex_stack &a, const complex_stack &b) {
            if (&b == &a) {
                return;
            }
            delete[] a.data;
            a.data = new complex[b.capacity];
            a.sz = b.sz;
            a.capacity = b.capacity;
            for (size_t i = 0; i < sz; i++) {
                a.data[i] = b.data[i];
            }
        }

    public:
        complex_stack() = default;

        complex_stack(const complex_stack &st) {
            move_(*this, st);
        }

        complex_stack operator=(const complex_stack &st) {
            move_(*this, st);
            return *this;
        }


        ~complex_stack() {
            delete[] data;
        }

        size_t size() const {
            return sz;
        }

        complex &operator[](const size_t i) const {
            return data[i];
        }

        friend complex_stack operator<<(const complex_stack &st, complex x);

        complex& operator+() const {
            return data[sz - 1];
        }

        friend complex_stack operator~(const complex_stack &st);
    };

    complex_stack operator<<(const complex_stack &st, complex x) {
        complex_stack tmp = st;
        if (tmp.sz == tmp.capacity) {
            tmp.increase();
        }
        tmp.data[tmp.sz] = x;
        tmp.sz++;
        return tmp;
    }

    complex_stack operator~(const complex_stack &st) {
        complex_stack tmp = st;
        tmp.sz--;
        return tmp;
    }
}