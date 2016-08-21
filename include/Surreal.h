#ifndef SURREAL_H_INCLUDED
#define SURREAL_H_INCLUDED

#include <iostream>
#include <set>

/*
G = {L | R}
    G > 0 means left player (L) can always win  (positive)
    G < 0 means right player (R) can always win (negative)
    G = 0 means 2nd player can always win       (zero)
    G | 0 means 1st player can always win       (fuzzy)
*/
enum SurrealSign{POSITIVE, NEGATIVE, ZERO, FUZZY};

class Surreal;

//Technically represents Games in general and not just Surreal numbers
class Surreal {
public:
    ///Simply using less does not work because of fuzzy games
    struct SurrealCompare {
        bool operator()(const Surreal& lhs, const Surreal& rhs) {
            return (lhs < rhs) ? true : (lhs | rhs);
        }
    };
    typedef std::set<Surreal, SurrealCompare> Set;

    Surreal();
    Surreal(int n);
    Surreal(const Surreal& a, const Surreal& b);
    Surreal(const Set& l, const Set& r);
    Surreal(const Surreal& orig);
    Surreal(Surreal&& orig);
    static Surreal Star(int n); ///"Constructor" for the nimbers *n
    ~Surreal();

    SurrealSign sign() const;
    Surreal pretty() const;

    Surreal& operator=(const Surreal& rhs) = default;
    Surreal& operator=(Surreal&& rhs) = default;

    bool operator<=(const Surreal& rhs) const;
    bool operator<(const Surreal& rhs) const;
    bool operator>=(const Surreal& rhs) const;
    bool operator>(const Surreal& rhs) const;
    bool operator==(const Surreal& rhs) const;
    bool operator!=(const Surreal& rhs) const;
    bool operator|(const Surreal& rhs) const;

    Set operator+(const Set& rhs) const;
    Surreal operator-() const;
    Surreal operator+(const Surreal& rhs) const;
    Surreal operator-(const Surreal& rhs) const;

    friend std::ostream& operator<<(std::ostream&, const Surreal&);
    friend std::ostream& operator<<(std::ostream&, const Set&);
private:
    bool print_pretty = false;
    Set left, right;
};

const Surreal star(0, 0);

std::ostream& operator<<(std::ostream& out, const Surreal& x);

#endif // SURREAL_H_INCLUDED
