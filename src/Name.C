/* Paul Rioux  4/9/10
 *
 * this class defines an item name.  It may be input
 * and output.
 */

#include "Name.h"

//-------------------------------------------------------------
/*
 * constructor
 */
 Name::Name()
 {
 }


 //-------------------------------------------------------------
/*
 * sets to string
 */
 Name::Name(string v) : value(v)
 {
 }

//-------------------------------------------------------------
/*
 * inputs a transaction description
 */
void Name::input(istream &s)
{
    s >> value;
}

//-------------------------------------------------------------
/*
 * outputs a transaction description
 */
void Name::output(ostream &s) const
{
    s << value;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool Name::operator != (const Name &v) const
{
    return !((*this) == v);
}

//-------------------------------------------------------------
bool Name::operator == (const Name &v) const
{
    return value == v.value;
}

// relational operators
bool Name::operator < (const Name &v) const
{
    return value < v.value;
}

// inputs using input operation above
istream & operator >> (istream & s, Name & v)
{
    v.input( s );
    return s;
}

// outputs using output operation above
ostream & operator << (ostream & s, const Name & v)
{
    v.output( s );
    return s;
}
