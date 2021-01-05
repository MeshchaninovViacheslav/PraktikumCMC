#include <iostream>
#include <string>
#include <array>
#include <cctype>

using namespace std;
/*
 * levels 0 to 5
 * 2
 * 21
 * 32
 * 321
 * 31
 * 311
 */
struct Result {
    array<bool, 6> fits;

    Result()
    {
        for(auto &it : fits) {
            it = true;
        }
    }

    void review(int lvl, int alt = -1)
    {
        switch (lvl) {
            case 5:
                fits[2] = (fits[2] && (alt == 3));
                fits[3] = (fits[3] && (alt == 3));
                break;
            case 4:
                fits[3] = fits[5] = false;
                fits[2] = (fits[2] && (alt == 2));
                break;
            case 3:
                fits[4] = (fits[4] && (alt == 5));
                fits[5] = (fits[5] && (alt == 5));
                break;
            case 2:
                fits[3] = fits[5] = false;
                fits[4] = (fits[4] && (alt == 4));
                break;
            case 1:
                for (int i = 2; i < 6; ++i) {
                    fits[i] = false;
                }
                break;
            case 0:
                for (int i = 1; i < 6; ++i) {
                    fits[i] = false;
                }
                break;
            default:
                exit(1);
        }
    }

    void print()
    {
        int i = 5;
        for(; i >= 0 && !fits[i]; --i) {}
        switch (i) {
            case 5:
                cout << "311" << endl;
                break;
            case 4:
                cout << "31" << endl;
                break;
            case 3:
                cout << "321" << endl;
                break;
            case 2:
                cout << "32" << endl;
                break;
            case 1:
                cout << "21" << endl;
                break;
            case 0:
                cout << "2" << endl;
                break;
            default:
                exit(1);
        }
    }
};

int main()
{
    string right;
    char left = 0;
    Result res;
    bool has_s_eps = false;
    bool has_eps = false;
    bool s_in_right = false;
    bool met_upper = false;
    while (cin >> left >> right) {
        if (right.size() == 1) {
            if (right[0] == '_') {
                if (left == 'S') {
                    has_s_eps = true;
                    res.review(3, 5);
                } else {
                    has_eps = true;
                    res.review(2, 4);
                }
            } else if (isupper(right[0])) {
                if (right[0] == 'S') {
                    s_in_right = true;
                }
                if (left != 'S') {
                    res.review(2, 4);
                } else {
                    if (met_upper) {
                        res.review(2, 4);
                    } else {
                        met_upper = true;
                        res.review(3, 5);
                    }
                }
            } else {
                res.review(3, 5);
            }
        } else if (right.size() == 2) {
            if ((islower(right[0]) || isdigit(right[0])) && isupper(right[1])) {
                res.review(3);
            } else if ((islower(right[1]) || isdigit(right[1])) && isupper(right[0])) {
                res.review(5);
            } else {
                res.review(1);
            }
            if (right[0] == 'S' || right[1] == 'S') {
                s_in_right = true;
            }
        } else {
            if (isupper(right[0])) {
                for (int i = 1; i < (int) right.size(); ++i) {
                    if (!islower(right[i]) && !isdigit(right[i])) {
                        res.review(1);
                    }
                    if (right[i] == 'S') {
                        s_in_right = true;
                    }
                }
                res.review(4);
                if (right[0] == 'S') {
                    s_in_right = true;
                }
            } else if (isupper(right[right.size() - 1])) {
                for (int i = 0; i < (int) right.size() - 1; ++i) {
                    if (!islower(right[i]) && !isdigit(right[i])) {
                        res.review(1);
                    }
                    if (right[i] == 'S') {
                        s_in_right = true;
                    }
                }
                res.review(2);
                if (right[right.size() - 1] == 'S') {
                    s_in_right = true;
                }
            } else {
                res.review(1);
            }
        }
    }

    if (has_eps || (has_s_eps && s_in_right)) {
        res.review(0);
    }

    res.print();

    return 0;
}