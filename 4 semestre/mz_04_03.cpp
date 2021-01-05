#include <vector>
#include <functional>
#include <iostream>

template<class T, class FUNC>
auto myapply(T begin, T end, FUNC f) {
    while (begin != end) {
        f(*begin);
        ++begin;
    }
}

template<class T, class FUNC>
auto myfilter2(T begin, T end, FUNC f) {
    std::vector<std::reference_wrapper<typename T::value_type>> v{};
    while (begin != end) {
        if (f(*begin)) {
            v.push_back(std::reference_wrapper<typename T::value_type>(*begin));
        }
        ++begin;
    }
    return v;
}

template<class T, class FUNC>
auto myapply(T* begin, T* end, FUNC f) {
    while (begin != end) {
        f(*begin);
        ++begin;
    }
}

template<class T, class FUNC>
auto myfilter2(T* begin, T* end, FUNC f) {
    std::vector<std::reference_wrapper<T>> v{};
    while (begin != end) {
        if (f(*begin)) {
            v.push_back(*begin);
        }
        ++begin;
    }
    return v;
}