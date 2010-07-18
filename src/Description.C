/* Paul Rioux  4/9/10
 *
 * this class defines an item description.  It may be input
 * and output.
 */

#include "Description.h"

//-------------------------------------------------------------
/*
 * inputs a transaction description
 */
void Description::input(istream &s)
{
    char temp;

    s >> temp;
    getline( s, value, '|' );
}

//-------------------------------------------------------------
/*
 * outputs a transaction description
 */
void Description::output(ostream &s) const
{
    s << value;
}

// outputs the description in the same
// format as the input
void Description::save(ostream &s) const
{
    s << '|' << value << '|';
}

// inputs using input operation above
istream & operator >> (istream & s, Description & v)
{
    v.input( s );
    return s;
}

// outputs using output operation above
ostream & operator << (ostream & s, const Description & v)
{
    v.output( s );
    return s;
}
