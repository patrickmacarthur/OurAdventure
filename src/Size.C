/* Paul Rioux  4/9/10
 *
 * this class defines a Size value.  These values may be input,
 * output and compared.  They may be positive or negative.
 * Size values may be added or subtracted.
*/

#include "Size.h"

//-------------------------------------------------------------
/*
 * constructs 0.00
 */
Size::Size()
{
    size = 0;
}

//-------------------------------------------------------------
/*
 * converts int to Size value
 */
Size::Size( int v )
{
    size = v;
}

//-------------------------------------------------------------
/*
 * returns true if greater than 0
 */
bool Size::isPositive() const
{
    return size > 0;
}

//-------------------------------------------------------------
/*
 * returns true if is 0
 */
bool Size::isZero() const
{
    return size == 0;
}

//-------------------------------------------------------------
/*
 * inputs Size in form of a float
 */
void Size::input(istream &s)
{
    s >> size;
}

//-------------------------------------------------------------
/*
 * outputs to stream in form of a float
 */
void Size::output(ostream &s) const
{
    s << size;
}

//-------------------------------------------------------------
bool Size::operator == (const Size &v) const
{
    return size == v.size;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool Size::operator != (const Size &v) const
{
    return size != v.size;
}

//-------------------------------------------------------------
bool Size::operator >= (const Size &v) const
{
    return size >= v.size;
}

//-------------------------------------------------------------
bool Size::operator > (const Size &v) const
{
    return size > v.size;
}

//-------------------------------------------------------------
bool Size::operator < (const Size &v) const
{
    return size < v.size;
}

//-------------------------------------------------------------
/*
 * relational operators
 */
bool Size::operator <= (const Size &v) const
{
    return size <= v.size;
}

//-------------------------------------------------------------
/*
 * simple addition
 */
Size Size::operator + (const Size &v) const
{
    return Size( size + v.size );
}

//-------------------------------------------------------------
/*
 * simple subtraction
 */
Size Size::operator - (const Size &v) const
{
    return Size( size - v.size );
}

//-------------------------------------------------------------
Size & Size::operator += (const Size &v)
{
    size += v.size;
    return *this;
}

//-------------------------------------------------------------
/*
 * augmented assignment operators
 */
Size & Size::operator -= (const Size &v)
{
    size -= v.size;
    return *this;
}

// inputs with named operation
istream & operator >> (istream &s, Size &v)
{
    v.input( s );
    return s;
}

// outputs with named operation
ostream & operator << (ostream &s, const Size &v)
{
    v.output( s );
    return s;
}
