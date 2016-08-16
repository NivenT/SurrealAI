#ifndef SURREAL_H_INCLUDED
#define SURREAL_H_INCLUDED

#include <iostream>
#include <set>

//Technically represents Games in general and not just Surreal numbers
class Surreal {
public:
    typedef std::set<Surreal> Set;

    Surreal();
    Surreal(int n);
    Surreal(const Surreal& a, const Surreal& b);
    Surreal(const Set& l, const Set& r);

    Surreal pretty() const;

    Surreal operator=(const Surreal& rhs);
    bool operator<=(const Surreal& rhs) const;
    bool operator<(const Surreal& rhs) const;
    bool operator>=(const Surreal& rhs) const;
    bool operator>(const Surreal& rhs) const;
    bool operator==(const Surreal& rhs) const;
    bool operator!=(const Surreal& rhs) const;

    Set operator+(const Set& rhs) const;
    Surreal operator+(const Surreal& rhs) const;

    friend std::ostream& operator<<(std::ostream&, const Surreal&);
    friend std::ostream& operator<<(std::ostream&, const Set&);
private:
    bool print_pretty = false;
    Set left, right;
};

std::ostream& operator<<(std::ostream& out, const Surreal& x);

#endif // SURREAL_H_INCLUDED
