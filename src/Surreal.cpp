#include "Surreal.h"

Surreal::Surreal() {
}

Surreal::Surreal(int n) {
    if (n > 0) {
        left.insert(Surreal(n-1));
    } else if (n < 0) {
        right.insert(Surreal(n+1));
    }
}

Surreal::Surreal(const Surreal& a, const Surreal& b) {
    left.insert(a);
    right.insert(b);
}

Surreal::Surreal(const Set& l, const Set& r) : left(l), right(r) {
}

Surreal Surreal::pretty() const {
    Surreal ret;
    for (const auto& xl : left) {
        ret.left.insert(xl.pretty());
    }
    for (const auto& xr : right) {
        ret.right.insert(xr.pretty());
    }
    ret.print_pretty = true;
    return ret;
}

std::ostream& operator<<(std::ostream& out, const Surreal::Set& xs) {
    for (auto it = xs.begin(); it != xs.end();) {
        auto& x = *it;
        if (x.print_pretty) {
            bool printed = false;
            if (x > 0) {
                for (int i = 0; x >= i; i++) {
                    if (x == i) {
                        out<<i;
                        printed = true;
                        break;
                    }
                }
            } else {
                for (int i = 0; x <= i; i--) {
                    if (x == i) {
                        out<<i;
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) {
                out<<x.pretty();
            }
        } else {
            out<<x;
        }
        if (++it != xs.end()) {
            out<<", ";
        }
    }
    return out;
}

Surreal Surreal::operator=(const Surreal& rhs) {
    left.clear();
    for (auto xl : rhs.left) {
        Surreal temp = xl;
        left.insert(temp);
    }
    right.clear();
    for (auto xr : rhs.right) {
        Surreal temp = xr;
        right.insert(temp);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Surreal& x) {
    return out<<"{ "<<x.left<<" | "<<x.right<<" }";
}

bool Surreal::operator<=(const Surreal& rhs) const {
    if (!rhs.right.empty()) {
        if (*rhs.right.begin() <= *this) {
            return false;
        }
    }
    if (!left.empty()) {
        if (rhs <= *(--left.end())) {
            return false;
        }
    }
    return true;
}

bool Surreal::operator<(const Surreal& rhs) const {
    return (*this <= rhs) && !(rhs <= *this);
}

bool Surreal::operator>=(const Surreal& rhs) const {
    return rhs <= *this;
}

bool Surreal::operator>(const Surreal& rhs) const {
    return !(*this <= rhs) && (rhs <= *this);
}

bool Surreal::operator==(const Surreal& rhs) const {
    return (*this <= rhs) && (rhs <= *this);
}

bool Surreal::operator!=(const Surreal& rhs) const {
    return !(*this <= rhs) || !(rhs <= *this);
}

Surreal::Set Surreal::operator+(const Set& rhs) const {
    Surreal::Set ret;
    for (const auto& x : rhs) {
        ret.insert(*this + x);
    }
    return ret;
}

Surreal Surreal::operator+(const Surreal& rhs) const {
    Surreal ret;

    Set xlpy = rhs + left;
    Set ylpx = *this + rhs.right;
    ret.left.insert(xlpy.begin(), xlpy.end());
    ret.left.insert(ylpx.begin(), ylpx.end());

    Set xrpy = rhs + right;
    Set yrpx = *this + rhs.right;
    ret.right.insert(xrpy.begin(), xrpy.end());
    ret.right.insert(yrpx.begin(), yrpx.end());

    return ret;
}