/* Paul Rioux  4/9/10
 *
 * this class defines an item id.  It may be input
 * and output.
 */

#include <iostream>
#include <string>
using namespace std;
#include "ID.h"

//-------------------------------------------------------------
/*
 * constructor
 */
ID::ID()
{
    value = "";
}

//-------------------------------------------------------------
/*
 * inputs an id
 */
void ID::input(istream &s)
{
    s >> value;
}

//-------------------------------------------------------------
/*
 * outputs an id
 */
void ID::output(ostream &s) const
{
    s << value;
}

//-------------------------------------------------------------
bool ID::operator == (const ID &v) const
{
    return value == v.value;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool ID::operator != (const ID &v) const
{
    return value != v.value;
}

//-------------------------------------------------------------
/*
 * relational operators
 */
bool ID::operator < (const ID &v) const
{
    return value < v.value;
}

//-------------------------------------------------------------
/*
 * returns id for a customer
 */
string ID::getID() const
{
    return value;
}

//-------------------------------------------------------------
/*
 * sets the id for a customer
 */
void ID::setID(string v)
{
    value = v;
}

// inputs using input operation above
istream & operator >> (istream & s, ID & v)
{
    v.input( s );
    return s;
}

// outputs using output operation above
ostream & operator << (ostream & s, const ID & v)
{
    v.output( s );
    return s;
}
