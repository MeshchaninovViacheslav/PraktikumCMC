#include <stdexcept>
#include <limits>
#include <iostream>
#include <sstream>
#include <type_traits>

namespace RangeImpl {
    template<typename T1, typename T2>
    bool check_over(const T1 &a) {
        T2 max_value = std::numeric_limits<T2>::max(), min_value = std::numeric_limits<T2>::min();
        return !(a > max_value || a < min_value);
    }

    template<typename T>
    bool check_over_sum(const T &a, const T &b) {
        if constexpr (std::is_integral_v<T>) {
            T max_value = std::numeric_limits<T>::max(), min_value = std::numeric_limits<T>::min(), zero_value = 0;
            if (a == zero_value || b == zero_value) {
                return true;
            }
            if (a > zero_value && b > zero_value) {
                return max_value - a >= b;
            }
            if (a < zero_value && b < zero_value) {
                return min_value - a <= b;
            }
            return true;
        } else {
            return true;
        }
    }

    template<typename T>
    bool check_over_sub(const T &a, const T &b) {
        if constexpr (std::is_integral_v<T>) {
            if (b == std::numeric_limits<T>::min()) {
                return false;
            }
            return check_over_sum(a, T(-b));
        } else {
            return true;
        }
    }

    template<typename T>
    bool check_over_mul(const T &a, const T &b) {
        if constexpr (std::is_integral_v<T>) {
            T max_value = std::numeric_limits<T>::max(), min_value = std::numeric_limits<T>::min(), zero_value = 0;
            if (a == zero_value || b == zero_value) {
                return true;
            }
            if ((a < zero_value && b > zero_value) || (a > zero_value && b < zero_value)) {
                if (a > zero_value) {
                    return min_value / a <= b;
                }
                return min_value / b <= a;
            } else {
                if (a == min_value || b == min_value) {
                    return false;
                }
                return max_value / abs(a) >= abs(b);

            }
        } else {
            return true;
        }
    }

    bool check_string_format(const std::string &s) {
        std::string::const_iterator end = s.end();
        std::string::const_iterator it = s.begin();
        if (it == end || *it != '(') {
            return false;
        }
        ++it;
        if (it != end && (*it == '-' || *it == '+')) {
            ++it;
        }
        while (it != end && std::isdigit(*it)) {
            ++it;
        }
        if (it == end || *it != ',') {
            return false;
        }
        ++it;
        while (it != end && isspace(*it)) {
            ++it;
        }
        if (it != end && (*it == '-' || *it == '+')) {
            ++it;
        }
        while (it != end && std::isdigit(*it)) {
            ++it;
        }
        if (it == end || *it != ')') {
            return false;
        }
        ++it;
        return it == end;
    }
}

template<typename T, class=std::enable_if_t<std::is_class_v<T> || (std::is_signed_v<T> && std::is_integral_v<T>)>>
class Range {
    T low, high;
public:
    Range(const T low = {}, const T high = {}) : low(low), high(high) {
        if (!(low <= high)) {
            throw std::invalid_argument("");
        }
    }

    Range(const Range &a) : low(a.low), high(a.high) {
        if (!(low <= high)) {
            throw std::invalid_argument("");
        }
    }

    explicit Range(const std::string &s) {
        if constexpr (std::is_integral_v<T>) {
            if (!RangeImpl::check_string_format(s)) {
                throw std::invalid_argument("");
            }
            std::stringstream ss(s);
            intmax_t l, r;
            if (!(((ss.ignore() >> l).ignore() >> r).ignore())) {
                throw std::range_error("");
            }
            if (!RangeImpl::check_over<intmax_t, T>(l) || !RangeImpl::check_over<intmax_t, T>(r)) {
                throw std::range_error("");
            }
            low = l;
            high = r;
        } else {
            auto it = s.begin();
            if (it != s.end() && *it == '(') {
                ++it;
            } else {
                throw std::invalid_argument("");
            }
            std::string l, r;
            while (it != s.end() && *it != ',') {
                l.push_back(*it);
                ++it;
            }
            if (it != s.end() && *it == ',') {
                ++it;
            } else {
                throw std::invalid_argument("");
            }
            while (it != s.end() && *it != ')') {
                r.push_back(*it);
                ++it;
            }
            if (it != s.end() && *it == ')') {
                ++it;
            } else {
                throw std::invalid_argument("");
            }
            if (it != s.end()) {
                throw std::invalid_argument("");
            }
            low = T(l);
            high = T(r);
        }
        if (!(low <= high)) {
            throw std::invalid_argument("");
        }
    }

    std::string to_string() const {
        std::stringstream ss;
        if constexpr (std::is_integral_v<T>) {
            ss << "(" << intmax_t(low) << "," << intmax_t(high) << ")";
        } else {
            ss << "(" << low << "," << high << ")";
        }
        return ss.str();
    }

    T get_low() const {
        return low;
    }

    T get_high() const {
        return high;
    }

    friend Range<T> operator+(const Range<T> &a, const Range<T> &b) {
        if (!RangeImpl::check_over_sum(a.get_low(), b.get_low()) ||
            !RangeImpl::check_over_sum(a.get_high(), b.get_high())) {
            throw std::overflow_error("");
        }
        return Range<T>{T(a.get_low() + b.get_low()), T(a.get_high() + b.get_high())};
    }

    friend Range<T> operator-(const Range<T> &a, const Range<T> &b) {
        if (!RangeImpl::check_over_sub(a.get_low(), b.get_high()) ||
            !RangeImpl::check_over_sub(a.get_high(), b.get_low())) {
            throw std::overflow_error("");
        }
        return Range<T>{T(a.get_low() - b.get_high()), T(a.get_high() - b.get_low())};
    }

    friend Range<T> operator*(const Range<T> &a, const Range<T> &b) {
        if (!RangeImpl::check_over_mul(a.get_low(), b.get_low()) ||
            !RangeImpl::check_over_mul(a.get_high(), b.get_low()) ||
            !RangeImpl::check_over_mul(a.get_low(), b.get_high()) ||
            !RangeImpl::check_over_mul(a.get_high(), b.get_high())) {
            throw std::overflow_error("");
        }
        return Range<T>{T(std::min(std::min(a.get_low() * b.get_low(), a.get_low() * b.get_high()),
                                   std::min(a.get_high() * b.get_low(), a.get_high() * b.get_high()))),
                        T(std::max(std::max(a.get_low() * b.get_low(), a.get_low() * b.get_high()),
                                   std::max(a.get_high() * b.get_low(), a.get_high() * b.get_high())))};
    }

    friend Range<T> operator-(const Range<T> &a) {
        if (!RangeImpl::check_over_sub((T) 0, a.get_low()) ||
            !RangeImpl::check_over_sub((T) 0, a.get_high())) {
            throw std::overflow_error("");
        }
        return Range<T>{T(-a.get_high()), T(-a.get_low())};
    }
};

/*
using namespace std;

struct Int {
    int i = 0;

    Int(int a = 0) : i(a) {}

    Int(const string &s){
        i = 0;
    }

    bool operator<=(const Int &b) const {
        return 1;
    }

    friend ostream &operator<<(ostream &ss, const Int &t) {
        ss << t.i;
        return ss;
    }

    friend Int operator+(const Int &a, const Int &b) {
        return Int(a.i + b.i);
    }

    friend Int operator-(const Int &a, const Int &b) {
        return Int(a.i - b.i);
    }

    bool operator==(const Int &b) const {
        return i == b.i;
    }

    bool operator>(const Int &b) const {
        return i > b.i;
    }

    bool operator<(const Int &b) const {
        return i < b.i;
    }
};

int main() {
    Range<char> t("(1,20)");
    std::cout << t.to_string();
}
*/