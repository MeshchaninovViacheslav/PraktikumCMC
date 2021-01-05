#include <iostream>
#include<map>
#include <string>

struct Pos {
    char cond, sym;

    bool operator==(const Pos &b) {
        return b.cond == cond && b.sym == sym;
    }

    bool operator<(const Pos &b) const {
        return sym == b.sym ? cond < b.cond : sym < b.sym;
    }

};

struct Res {
    Pos a;
    int dir;
};

int main() {
    std::string s;
    std::cin >> s;
    Res cur = {'S', s[0], 0};

    std::map<Pos, Res> data{
            {{'S', '0'}, {'S', '0', 1}},
            {{'S', '1'}, {'A', '1', 1}},
            {{'S', '#'}, {'S', '#', 1}},
            {{'A', '0'}, {'A', '0', 1}},
            {{'A', '1'}, {'S', '1', 1}},
            {{'A', '#'}, {'B', '#', -1}},
            {{'B', '0'}, {'B', '0', -1}},
            {{'B', '1'}, {'B', '1', -1}},
            {{'B', '#'}, {'C', '#', 1}},
            {{'C', '0'}, {'C', '0', 1}},
            {{'C', '1'}, {'D', '0', 0}},
            {{'D', '0'}, {'D', '0', 0}}
    };

    while (cur.dir != (int)s.length() && cur.dir != -1 && !(cur.a == (Pos) {'D', '0'})) {
        Res t = data[cur.a];
        s[cur.dir] = t.a.sym;
        cur.a.cond = t.a.cond;
        cur.dir += t.dir;
        cur.a.sym = s[cur.dir];
    }
    std::cout << s << std::endl;
    return 0;
}