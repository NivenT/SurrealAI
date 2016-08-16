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

Surreal Surreal::Star(int n) {
    Surreal ret;
    for (int i = 0; i < n; i++) {
        Surreal temp = Surreal::Star(i);
        ret.left.insert(temp);
        ret.right.insert(temp);
    }
    return ret;
}

Surreal::~Surreal() {
    left.clear();
    right.clear();
}

SurrealSign Surreal::sign() const {
    if (*this > 0) {
        return POSITIVE;
    } else if (*this < 0) {
        return NEGATIVE;
    } else if (*this == 0) {
        return ZERO;
    } else {
        return FUZZY;
    }
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
        const auto& x = *it;
        bool printed = false;
        if (x.print_pretty) {
            int step = x > 0 ? 1 : -1;
            Surreal cmp = x > 0 ? x : -x;
            for (int i = 0; cmp >= i*step; i += step) {
                if (x == i) {
                    out<<i;
                    printed = true;
                }
            }
            if (x == star) {
                out<<"*";
                printed = true;
            }
            //Messy, but I haven't thought of anything better
            if (!printed) for(int i = 2; i < 10; i++) {
                if (x == Surreal::Star(i)) {
                    out<<"*"<<i;
                    printed = true;
                    break;
                }
            }
        }
        if (!printed) {
            out<<x;
        }
        if (++it != xs.end()) {
            out<<", ";
        }
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Surreal& x) {
    return out<<"{ "<<x.left<<" | "<<x.right<<" }";
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

bool Surreal::operator<=(const Surreal& rhs) const {
    for (const auto& xl : left) {
        if (rhs <= xl) {
            return false;
        }
    }
    for (const auto& yr : rhs.right) {
        if (yr <= *this) {
            return false;
        }
    }
    /* Unsure if still correct with the modified Set ordering
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
    */
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

Surreal Surreal::operator-() const {
    Surreal ret;
    for (const auto& xl : left) {
        ret.right.insert(-xl);
    }
    for (const auto& xr : right) {
        ret.left.insert(-xr);
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

Surreal Surreal::operator-(const Surreal& rhs) const {
    return *this + -rhs;
}
