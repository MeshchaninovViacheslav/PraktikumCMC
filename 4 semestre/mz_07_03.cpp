#include <iostream>

class S {
    int val = 0;
    int cnt = 1;
    bool flag = true;
public:
    S() {
        int a;
        if (!(std::cin >> a)) {
            cnt = 0;
            a = 0;
            flag = false;
        }
        val = a;
    }

    S( S &d) {
        int a;
        if (!(std::cin >> a)) {
            a = 0;
            flag = false;
        }
        val = a + d.val;
        d.cnt = 0;
    }

    S( S &&d) {
        int a;
        if (!(std::cin >> a)) {
            a = 0;
            flag = false;
        }
        val = a + d.val;
        d.cnt = 0;
    }

    explicit operator bool() {
        return flag;
    }

    ~S() {
        if (cnt) {
            std::cout << val << std::endl;
        }
    }
};
