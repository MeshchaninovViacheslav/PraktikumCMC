//
// Created by vyacheslav on 19.04.2020.
//

#ifndef PRAK_SP_COMPLEX_H
#define PRAK_SP_COMPLEX_H
class complex {
private:
    double Re, Im;
public:
    complex(const double re = 0, const double im = 0) : Re(re), Im(im) {};

    explicit complex(const std::string &s) {
        std::stringstream ss(s);
        ss.ignore();
        ss >> Re;
        ss.ignore();
        ss >> Im;
        ss.ignore();
    }

    double re() const {
        return Re;
    }

    double im() const {
        return Im;
    }

    double abs2() const {
        return Re * Re + Im * Im;
    }

    double abs() const {
        return std::sqrt(abs2());
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << '(' << std::setprecision(10) << Re << "," << Im << ')';
        std::string s;
        getline(ss, s);
        return s;
    }

    complex &operator+=(const complex &b) {
        Re += b.Re, Im += b.Im;
        return *this;
    }

    complex &operator-=(const complex &b) {
        Re -= b.Re, Im -= b.Im;
        return *this;
    }

    complex &operator*=(const complex &b) {
        double re_tmp = Re * b.Re - Im * b.Im;
        double im_tmp = Re * b.Im + Im * b.Re;
        Re = re_tmp;
        Im = im_tmp;
        return *this;
    }

    complex &operator/=(const complex &b) {
        double re_tmp = (Re * b.Re + Im * b.Im) / b.abs2();
        double im_tmp = (-Re * b.Im + Im * b.Re) / b.abs2();
        Re = re_tmp;
        Im = im_tmp;
        return *this;
    }

    friend complex operator+(const complex &a, const complex &b);

    friend complex operator-(const complex &a, const complex &b);

    friend complex operator*(const complex &a, const complex &b);

    friend complex operator/(const complex &a, const complex &b);


    friend complex operator~(const complex &a);

    friend complex operator-(const complex &a);
};

complex operator~(const complex &a) {
    return complex{a.Re, -a.Im};
}

complex operator-(const complex &a) {
    return complex{-a.Re, -a.Im};
}

complex operator+(const complex &a, const complex &b) {
    complex t = a;
    t += b;
    return t;
}

complex operator-(const complex &a, const complex &b) {
    complex t = a;
    t -= b;
    return t;
}

complex operator*(const complex &a, const complex &b) {
    complex t = a;
    t *= b;
    return t;
}

complex operator/(const complex &a, const complex &b) {
    complex t = a;
    t /= b;
    return t;
}
#endif //PRAK_SP_COMPLEX_H
