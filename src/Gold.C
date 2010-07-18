/* Paul Rioux  4/9/10
 *
 * this class defines a Gold value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Gold values may be added or subtracted.
*/

#include <iostream>
using namespace std;
#include "Gold.h"

//-------------------------------------------------------------
/*
 * constructs 0.00
 */
Gold::Gold()
{
    points = 0;
}

//-------------------------------------------------------------
/*
 * converts float to Gold value
 */
Gold::Gold(float v)
{
    points = (int) v;
}

//-------------------------------------------------------------
/*
 * converts int to Gold value
 */
Gold::Gold( int v )
{
    points = v;
}

//-------------------------------------------------------------
/*
 * returns true if greater than 0
 */
bool Gold::isPositive() const
{
    return points > 0;
}

//-------------------------------------------------------------
/*
 * returns true if less than 0
 */
bool Gold::isNegative() const
{
    return points < 0;
}

//-------------------------------------------------------------
/*
 * returns true if is 0
 */
bool Gold::isZero() const
{
    return points == 0;
}

//-------------------------------------------------------------
/*
 * inputs Gold in form of a int
 */
void Gold::input(istream &s)
{
    s >> points;
}

//-------------------------------------------------------------
/*
 * outputs to stream in form of a int
 */
void Gold::output(ostream &s) const
{
    s << points;
}

//-------------------------------------------------------------
bool Gold::operator == (const Gold &v) const
{
    return points == v.points;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool Gold::operator != (const Gold &v) const
{
    return points != v.points;
}

//-------------------------------------------------------------
bool Gold::operator >= (const Gold &v) const
{
    return points >= v.points;
}

//-------------------------------------------------------------
bool Gold::operator > (const Gold &v) const
{
    return points > v.points;
}

//-------------------------------------------------------------
bool Gold::operator < (const Gold &v) const
{
    return points < v.points;
}

//-------------------------------------------------------------
/*
 * relational operators
 */
bool Gold::operator <= (const Gold &v) const
{
    return points <= v.points;
}

//-------------------------------------------------------------
/*
 * negation
 */
Gold Gold::operator - () const
{
    return Gold( -points );
}

//-------------------------------------------------------------
/*
 * simple addition
 */
Gold Gold::operator + (const Gold &v) const
{
    return Gold( points + v.points );
}

//-------------------------------------------------------------
/*
 * simple subtraction
 */
Gold Gold::operator - (const Gold &v) const
{
    return Gold( points - v.points );
}

//-------------------------------------------------------------
Gold & Gold::operator += (const Gold &v)
{
    points += v.points;
    return *this;
}

//-------------------------------------------------------------
/*
 * augmented assignment operators
 */
Gold & Gold::operator -= (const Gold &v)
{
    points -= v.points;
    return *this;
}

//-------------------------------------------------------------
/*
 * multiplies Gold value by float
 */
Gold Gold::operator * (float v) const
{
    return Gold( points * v );
}

// inputs with named operation
istream & operator >> (istream &s, Gold &v)
{
    v.input( s );
    return s;
}

// outputs with named operation
ostream & operator << (ostream &s, const Gold &v)
{
    v.output( s );
    return s;
}

// inverts arguments and calls member operator
Gold operator * (float v1, const Gold &v2)
{
    return v2 * v1;
}
