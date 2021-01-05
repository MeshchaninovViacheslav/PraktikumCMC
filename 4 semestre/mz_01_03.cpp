class Sub {
private:
    int a, b;
public:
    Sub(int a = 0, int b = 0): a(a), b(b) {};
    Sub(const Sub &a, const Sub& b): a(a.value()), b(b.value()) {};
    int value() const {
        return a - b;
    }
};