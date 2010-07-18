/* Paul Rioux  4/9/10
 *
 * this class defines an item to be found in a
 * dungeon.  It may be input and output as well
 * as cloned.
 */

#include <iostream>
#include <string>
using namespace std;
//#include "Map.h"
#include "LockState.h"
#include "Item.h"

//-------------------------------------------------------------
/*
 * destructor
 */
Item::~Item()
{
}


//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Item::input(istream & s, Map *m)
{
    s >> itemID >> name >> description;
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Item::save(ostream & s) const
{
    s << "item " << itemID << ' ' << name << ' ';
    description.save( s );
}

//-------------------------------------------------------------
/*
 * prints name of item to stream
 */
void Item::printName(ostream & s) const
{
    s << name;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Item::printDescription(ostream & s) const
{
    s << description << '\n';
}

//-------------------------------------------------------------
/*
 * returns a constant reference to ID
 */
const ID& Item::getID() const
{
    return itemID;
}

//-------------------------------------------------------------
/*
 * returns a constant reference to Name
 */
const Name& Item::getName() const
{
    return name;
}

// Sets the state of the door: open or closed.
void Item::setState( LockState * state )
{
    delete state;
}

/*
// outputs using named operation
istream & operator >> (istream & s, Item & v)
{
    v.input( s );
    return s;
}
*/

// outputs using named operation
ostream & operator << (ostream & s, const Item & v)
{
    v.printDescription( s );
    return s;
}
