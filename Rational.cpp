#include <numeric>
#include <tuple>
class Rational {
private:
    int num, den;
    void normalize() {
        int g = std::gcd(std::abs(num), std::abs(den));
        num /= g;
        den /= g;
        if (den < 0) {
            num = -num, den = -den;
        }
    }

public:
    Rational() : num(0), den(1) {}
    Rational(int _num, int _den) : num(_num), den(_den) {
        normalize();
    }
    Rational(int x) : num(x), den(1) {
        normalize();
    }
    int numerator() const {
        return num;
    }
    int denominator() const {
        return den;
    }
    Rational operator+() const {
        return *this;
    }
    Rational operator-() const {
        return Rational(-num, den);
    }
    Rational& operator+=(const Rational&x) {
        *this = Rational(num * x.den + x.num * den, x.den * den);
        return *this;
    }
    Rational& operator+=(int x) {
        *this += Rational(x);
        normalize();
        return *this;
    }
    Rational& operator-=(const Rational&x) {
        *this = Rational(num * x.den - x.num * den, x.den * den);
        return *this;
    }
    Rational& operator-=(int x) {
        *this -= Rational(x);
        normalize();
        return *this;
    }
    Rational& operator*=(const Rational&x) {
        *this = Rational(num * x.num, x.den * den);
        return *this;
    }
    Rational& operator*=(int x) {
        *this *= Rational(x);
        normalize();
        return *this;
    }
    Rational& operator/=(const Rational&x) {
        *this = Rational(num * x.den, x.num * den);
        return *this;
    }
    Rational& operator/=(int x) {
        *this /= Rational(x);
        normalize();
        return *this;
    }
    bool operator==(const Rational& x) const {
        return std::tie(num, den) == std::tie(x.num, x.den);
    }
    bool operator!=(const Rational& x) const {
        return !(x == *this);
    }
    Rational& operator++() {
        num += den;
        normalize();
        return *this;
    }
    Rational operator++(int) {
        Rational old(num, den);
        num += den;
        normalize();
        return old;
    }
    Rational& operator--() {
        num -= den;
        normalize();
        return *this;
    }
    Rational operator--(int) {
        Rational old(num, den);
        num -= den;
        normalize();
        return old;
    }
};
Rational operator+(Rational x, const Rational& y) {
    return x += y;
}
Rational operator+(Rational x, int y) {
    return x += Rational(y);
}
Rational operator+(int lhs, const Rational& x) {
    return x + lhs;
}

Rational operator-(Rational x, const Rational& y) {
    return x -= y;
}
Rational operator-(Rational x, int y) {
    return x -= Rational(y);
}
Rational operator-(int lhs, const Rational& x) {
    return -x + Rational(lhs);
}

Rational operator*(Rational y, const Rational &x) {
    return y *= x;
}
Rational operator*(const Rational &x, int rhs) {
    return x * Rational(rhs);
}
Rational operator*(int lhs, const Rational &x) {
    return x * lhs;
}

Rational operator/(Rational y, const Rational &x) {
    return y /= x;
}
Rational operator/(const Rational& y, int lhs) {
    return y / Rational(lhs);
}
Rational operator/(int lhs, const Rational& y) {
    return Rational(lhs) / y;
}
