class Sum {
private:
    int a, b;
public:
    Sum(int a, int b): a(a), b(b) {};
    Sum(const Sum &a, int b): a(a.get()), b(b) {};
    int get() const {
        return a + b;
    }
};