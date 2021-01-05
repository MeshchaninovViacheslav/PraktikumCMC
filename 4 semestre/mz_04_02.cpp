template<class T, class FUNC>
auto myfilter(const T& a, FUNC pred) {
    T ans{};
    for (auto x: a) {
        if (pred(x)) {
            ans.insert(ans.end(), x);
        }
    }
    return ans;
}