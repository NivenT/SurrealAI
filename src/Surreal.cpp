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

/**/
Surreal::Surreal(const Surreal& orig) : print_pretty(orig.print_pretty) {
    for (auto& xl : orig.left) {
        left.insert(xl);
    }
    for (auto& xr : orig.right) {
        right.insert(xr);
    }
}

Surreal::Surreal(Surreal&& orig) : print_pretty(orig.print_pretty), left(orig.left), right(orig.right) {
    orig.print_pretty = false;
    orig.left.clear();
    orig.right.clear();
}
/**/

Surreal Surreal::Star(int n) {
    Surreal nimbers[n+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            nimbers[i].left.insert(nimbers[j]);
            nimbers[i].right.insert(nimbers[j]);
        }
    }
    return nimbers[n];
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

Surreal Surreal::simplify() const {
    Surreal ret;
    if (!left.empty()) {
        Surreal maximum = *left.begin();
        for (auto it = std::next(left.begin(), 1); it != left.end(); ++it) {
            if (maximum <= *it) {
                maximum = *it;
            }
        }
        for (auto it = std::next(left.begin(), 1); it != left.end(); ++it) {
            if (maximum || *it) {
                ret.left.insert(*it);
            }
        }
        ret.left.insert(maximum);
    }
    if (!right.empty()) {
        Surreal minimum = *right.begin();
        for (auto it = std::next(right.begin(), 1); it != right.end(); ++it) {
            if (*it <= minimum) {
                minimum = *it;
            }
        }
        for (auto it = std::next(right.begin(), 1); it != right.end(); ++it) {
            if (*it || minimum) {
                ret.right.insert(*it);
            }
        }
        ret.right.insert(minimum);
    }
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

bool Surreal::operator||(const Surreal& rhs) const {
    return !(*this <= rhs) && !(rhs <= *this);
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
    Set ylpx = *this + rhs.left;
    for (const auto& xl : xlpy) {
        ret.left.insert(xl);
    }
    for (const auto& xl : ylpx) {
        ret.left.insert(xl);
    }

    Set xrpy = rhs + right;
    Set yrpx = *this + rhs.right;
    for (const auto& xr : xrpy) {
        ret.right.insert(xr);
    }
    for (const auto& xr : yrpx) {
        ret.right.insert(xr);
    }

    return ret;
}

Surreal Surreal::operator-(const Surreal& rhs) const {
    return *this + -rhs;
}
