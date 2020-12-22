#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
template <typename T>
class Polynomial {
private:
    std::vector<T> data;
    void begin_clear() {
        while (!data.empty() && data.back() == T()) data.pop_back();
    }

public:
    Polynomial(const std::vector<T>&x) : data(x) {
        begin_clear();
    }
    Polynomial(T z = T()) : data{{z}} {
        begin_clear();
    }
    template <typename Iter>
    Polynomial(Iter begin, Iter end) : data(begin, end) {
        begin_clear();
    }
    auto begin() const {
        return data.begin();
    }
    auto end() const {
        return data.end();
    }
    const T operator[] (size_t i) const {
        if (i >= data.size())
            return T();
        return data[i];
    }
    int Degree() const {
        return (data.empty() ? -1 : data.size() - 1);
    }
    Polynomial& operator+=(const Polynomial& x) {
        data.resize(std::max(x.data.size(), data.size()));
        for (size_t i = 0; i < x.data.size(); ++i) {
            data[i] += x[i];
        }
        begin_clear();
        return *this;
    }
    Polynomial& operator+=(T x) {
        return (*this += Polynomial(x));
    }
    Polynomial& operator-=(const Polynomial& x) {
        data.resize(std::max(x.data.size(), data.size()));
        for (size_t i = 0; i < x.data.size(); ++i) {
            data[i] -= x[i];
        }
        begin_clear();
        return *this;
    }
    Polynomial& operator-=(T x) {
        return (*this -= Polynomial(x));
    }
    Polynomial operator+(const Polynomial& x) const {
        Polynomial<T>z(data);
        z += x;
        return z;
    }
    Polynomial operator-(const Polynomial& x) const {
        Polynomial<T>z(data);
        z -= x;
        return z;
    }
    Polynomial operator+(const T x) const {
        Polynomial<T>z(data);
        z += Polynomial(x);
        return z;
    }
    Polynomial operator-(const T x) const {
        Polynomial<T>z(data);
        z -= Polynomial(x);
        return z;
    }

    bool operator==(const Polynomial& x) const {
        return x.data == data;
    }
    bool operator!=(const Polynomial &x) const {
        return x.data != data;
    }
    Polynomial& operator+() const {
        return *this;
    }
    Polynomial& operator-() {
        for (size_t i = 0; i < data.size(); i++) {
            data[i] = -data[i];
        }
        return *this;
    }
    T operator()(T x) const {
        if (data.empty()) return T();
        T to_ret = T();
        for (int i = data.size() - 1; i >= 0; i--) {
            to_ret = to_ret * x + data[i];
        }
        return to_ret;
    }
    Polynomial& operator*=(const Polynomial& x) {
        Polynomial<T>z;
        z.data.resize(x.data.size() * data.size() + 1);
        fill(z.data.begin(), z.data.end(), T());
        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = 0; j < x.data.size(); j++) {
                z.data[i + j] += data[i] * x.data[j];
            }
        }
        *this = z;
        begin_clear();
        return *this;
    }
    Polynomial& operator*=(T x) {
        return (*this *= Polynomial(x));
    }
    Polynomial operator*(const Polynomial& x) const {
        Polynomial<T>z(data);
        z *= x;
        return z;
    }
    Polynomial operator*(const T x) const {
        Polynomial<T>z(data);
        z *= Polynomial(x);
        return z;
    }
    Polynomial operator&(const Polynomial& x) const {
        Polynomial<T>z(x);
        Polynomial<T>summary;
        for (int i = 0; i <= Degree(); i++) {
            Polynomial<T>monomial(data[i]);
            for (int j = 0; j < i; j++) {
                monomial *= x;
            }
            summary += monomial;
        }
        return summary;
    }
};
template <typename T>
Polynomial<T> operator+(const T lhs, const Polynomial<T>& rhs) {
    return rhs + lhs;
}
template <typename T>
Polynomial<T> operator-(const T lhs, const Polynomial<T>& rhs) {
    return -rhs + lhs;
}
template <typename T>
Polynomial<T> operator*(const T lhs, const Polynomial<T>& rhs) {
    return rhs * lhs;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& x) {
    if (x.Degree() == -1) {
        os << T();
    } else if (x.Degree() == 0) {
        os << x[0];
    } else {
        for (int i = x.Degree(); i >= 0; i--) {
            if (x[i] == T()) continue;
            if (x[i] < T()) {
                os << '-';
            } else {
                if (i != x.Degree()) {
                    os << '+';
                }
            }
            T val = x[i];
            if (val < T()) {
                val = -val;
            }
            bool is_one = (val == T(1));
            if (i == 0) {
                os << val;
            } else {
                if (!is_one)
                    os << val << "*";
                os << "x";
                if (i != 1) os << "^" << i;
            }
        }
    }
    return os;
}



