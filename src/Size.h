#ifndef SIZE_H
#define SIZE_H

/* Paul Rioux  4/9/10
 *
 * this class defines a Size value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Size values may be added or subtracted.
*/

#include <iostream>
using namespace std;

class Size {

    public:

        Size();
            // constructs 0.00

        Size( int v );
            // converts int to Size value

        bool isPositive() const;
            // returns true if greater than 0

        bool isZero() const;
            // returns true if is 0

        void input(istream &s);
            // inputs Size in form of a float

        void output(ostream &s) const;
            // outputs to stream in form of a float

        bool operator == (const Size &v) const;
        bool operator != (const Size &v) const;
            // equality operators

        bool operator >= (const Size &v) const;
        bool operator > (const Size &v) const;
        bool operator < (const Size &v) const;
        bool operator <= (const Size &v) const;
            // relational operators

        Size operator + (const Size &v) const;
            // simple addition

        Size operator - (const Size &v) const;
            // simple subtraction

        Size & operator += (const Size &v);
        Size & operator -= (const Size &v);
            // augmented assignment operators

    private:

        int size;
};

istream & operator >> (istream &s, Size &v);
    // inputs with named operation

ostream & operator << (ostream &s, const Size &v);
    // outputs with named operation

#endif
