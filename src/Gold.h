#ifndef GOLD_H
#define GOLD_H

/* Paul Rioux  4/9/10
 *
 * this class defines a Gold value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Gold values may be added or subtracted.
*/

#include <iostream>
using namespace std;

class Gold {
    public:
        Gold();
            // constructs 0.00

        Gold(float);
            // converts float to Gold value

        Gold( int v );
            // converts int to Gold value

        bool isPositive() const;
            // returns true if greater than 0

        bool isNegative() const;
            // returns true if less than 0

        bool isZero() const;
            // returns true if is 0

        void input(istream &s);
            // inputs Gold in form of a float

        void output(ostream &s) const;
            // outputs to stream in form of a float

        bool operator == (const Gold &v) const;
        bool operator != (const Gold &v) const;
            // equality operators

        bool operator >= (const Gold &v) const;
        bool operator > (const Gold &v) const;
        bool operator < (const Gold &v) const;
        bool operator <= (const Gold &v) const;
            // relational operators

        Gold operator - () const;
            // negation

        Gold operator + (const Gold &v) const;
            // simple addition

        Gold operator - (const Gold &v) const;
            // simple subtraction

        Gold & operator += (const Gold &v);
        Gold & operator -= (const Gold &v);
            // augmented assignment operators

        Gold operator * (float) const;
            // multiplies Gold value by float

    private:

        int points;
};

istream & operator >> (istream &s, Gold &v);
    // inputs with named operation

ostream & operator << (ostream &s, const Gold &v);
    // outputs with named operation

Gold operator * (float v1, const Gold &v2);
    // inverts arguments and calls member operator

#endif
