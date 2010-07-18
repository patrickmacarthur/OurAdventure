/* Paul Rioux  4/9/10
 *
 * this class defines a weight value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Weight values may be added or subtracted.
*/

#include <iostream>
using namespace std;
#include "Weight.h"

//-------------------------------------------------------------
/*
 * constructs 0.00
 */
Weight::Weight()
{
    weight = 0;
}

//-------------------------------------------------------------
/*
 * converts int to Weight value
 */
Weight::Weight( int v )
{
    weight = v;
}

//-------------------------------------------------------------
/*
 * returns true if greater than 0
 */
bool Weight::isPositive() const
{
    return weight > 0;
}

//-------------------------------------------------------------
/*
 * returns true if is 0
 */
bool Weight::isZero() const
{
    return weight == 0;
}

//-------------------------------------------------------------
/*
 * inputs Weight in form of a float
 */
void Weight::input(istream &s)
{
    s >> weight;
}

//-------------------------------------------------------------
/*
 * outputs to stream in form of a float
 */
void Weight::output(ostream &s) const
{
    s << weight;
}

//-------------------------------------------------------------
bool Weight::operator == (const Weight &v) const
{
    return weight == v.weight;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool Weight::operator != (const Weight &v) const
{
    return weight != v.weight;
}

//-------------------------------------------------------------
bool Weight::operator >= (const Weight &v) const
{
    return weight >= v.weight;
}

//-------------------------------------------------------------
bool Weight::operator > (const Weight &v) const
{
    return weight > v.weight;
}

//-------------------------------------------------------------
bool Weight::operator < (const Weight &v) const
{
    return weight < v.weight;
}

//-------------------------------------------------------------
/*
 * relational operators
 */
bool Weight::operator <= (const Weight &v) const
{
    return weight <= v.weight;
}

//-------------------------------------------------------------
/*
 * simple addition
 */
Weight Weight::operator + (const Weight &v) const
{
    return Weight( weight + v.weight );
}

//-------------------------------------------------------------
/*
 * simple subtraction
 */
Weight Weight::operator - (const Weight &v) const
{
    return Weight( weight - v.weight );
}

//-------------------------------------------------------------
/*
 * simple muliplication
 */
Weight Weight::operator * (float v) const
{
    int x = (int) (weight * v);
    return Weight( x );
}

//-------------------------------------------------------------
Weight & Weight::operator += (const Weight &v)
{
    weight += v.weight;
    return *this;
}

//-------------------------------------------------------------
/*
 * augmented assignment operators
 */
Weight & Weight::operator -= (const Weight &v)
{
    weight -= v.weight;
    return *this;
}

// inputs with named operation
istream & operator >> (istream &s, Weight &v)
{
    v.input( s );
    return s;
}

// outputs with named operation
ostream & operator << (ostream &s, const Weight &v)
{
    v.output( s );
    return s;
}
