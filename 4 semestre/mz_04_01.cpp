template<class T>
auto process(const T& a) {
    typename T::value_type sum{};
    auto it = a.rbegin();
    for(int i = 0; it != a.rend(); ++it, ++i) {
        if (i == 0 || i == 2 || i == 4) {
            sum += *it;
        }
    }
    return sum;
}