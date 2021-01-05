#include <iostream>

bool Scan_G(std::string &s) {
    int i = 0;
    char c;
    enum state {
        H, A, AB, AC, AS, ABS, ABC, ACS, ABCS, S, ER
    };
    state CS = H;
    c = s[i++];
    do {
        switch (CS) {
            case H:
                if (c == '0') {
                    CS = A;
                    c = s[i++];
                } else if (c == '1') {
                    CS = AB;
                    c = s[i++];
                } else {
                    CS = ER;
                }
                break;
            case A:
                if (c == '0') {
                    CS = A;
                    c = s[i++];
                } else if (c == '1') {
                    CS = AB;
                    c = s[i++];
                } else {
                    CS = ER;
                }
                break;
            case AB:
                if (c == '0') {
                    CS = AC;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABC;
                    c = s[i++];
                } else {
                    CS = ER;
                }
                break;
            case AC:
                if (c == '0') {
                    CS = AS;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABS;
                    c = s[i++];
                } else {
                    CS = ER;
                }
                break;
            case AS:
                if (c == '0') {
                    CS = A;
                    c = s[i++];
                } else if (c == '1') {
                    CS = AB;
                    c = s[i++];
                } else if (c == '#') {
                    CS = S;
                } else {
                    CS = ER;
                }
                break;
            case ABS:
                if (c == '0') {
                    CS = AC;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABC;
                    c = s[i++];
                } else if (c == '#') {
                    CS = S;
                } else {
                    CS = ER;
                }
                break;
            case ABC:
                if (c == '0') {
                    CS = ACS;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABCS;
                    c = s[i++];
                } else {
                    CS = ER;
                }
                break;
            case ACS:
                if (c == '0') {
                    CS = AS;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABS;
                    c = s[i++];
                } else if (c == '#') {
                    CS = S;
                } else {
                    CS = ER;
                }
                break;
            case ABCS:
                if (c == '0') {
                    CS = ACS;
                    c = s[i++];
                } else if (c == '1') {
                    CS = ABCS;
                    c = s[i++];
                } else if (c == '#') {
                    CS = S;
                } else {
                    CS = ER;
                }
                break;
            default:
                break;
        }
    } while (CS != S && CS != ER);
    return CS == S;
}

int main() {
    std::string s;
    while (std::cin >> s) {
        s.push_back('#');
        if (Scan_G(s)) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}