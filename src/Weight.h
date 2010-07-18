#ifndef WEIGHT_H
#define WEIGHT_H

/* Paul Rioux  4/9/10
 *
 * this class defines a weight value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Weight values may be added or subtracted.
*/

#include <iostream>
using namespace std;

class Weight {

    public:

        Weight();
            // constructs 0.00

        Weight( int v );
            // converts int to Weight value

        bool isPositive() const;
            // returns true if greater than 0

        bool isZero() const;
            // returns true if is 0

        void input(istream &s);
            // inputs Weight in form of a float

        void output(ostream &s) const;
            // outputs to stream in form of a float

        bool operator == (const Weight &v) const;
        bool operator != (const Weight &v) const;
            // equality operators

        bool operator >= (const Weight &v) const;
        bool operator > (const Weight &v) const;
        bool operator < (const Weight &v) const;
        bool operator <= (const Weight &v) const;
            // relational operators

        Weight operator + (const Weight &v) const;
            // simple addition

        Weight operator - (const Weight &v) const;
            // simple subtraction

        Weight operator * (float v) const;
            // simple multiplication

        Weight & operator += (const Weight &v);
        Weight & operator -= (const Weight &v);
            // augmented assignment operators

    private:

        int weight;
};

istream & operator >> (istream &s, Weight &v);
    // inputs with named operation

ostream & operator << (ostream &s, const Weight &v);
    // outputs with named operation

#endif
