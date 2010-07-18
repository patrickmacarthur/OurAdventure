/* Paul Rioux  4/9/10
 *
 * this class defines an item which can be carryed
 * This would include packs, consumeables, keys,
 * and treasure.
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "Carryable.h"
#include "Item.h"
#include "Gold.h"
#include "Weight.h"
#include "Size.h"
#include "Map.h"

//-------------------------------------------------------------
/*
 * destructor
 */
Carryable::~Carryable()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Carryable::clone() const
{
    return new Carryable(*this);
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Carryable::addToMap(Map *v)
{
    v->add( this );

    // remove this later
    cout << "Carryable added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Carryable::input(istream & s, Map *m)
{
    s >> itemID >> name >> description >> weight >> size;
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Carryable::save(ostream & s) const
{
    s << "Carryable " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << weight << ' ' << size;
}

//-------------------------------------------------------------
/*
 * returns weight of item
 */
Weight Carryable::getWeight() const
{
    return weight;
}

//-------------------------------------------------------------
/*
 * returns size of item
 */
Size Carryable::getSize() const
{
    return size;
}

//-------------------------------------------------------------
/*
 * returns gold value of item
 */
Gold Carryable::getPoints() const
{
    return Gold(0);
}

//-------------------------------------------------------------
/*
 * returns health value of item.  May
 * be negative
 */
int Carryable::getHealth() const
{
    return 0;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Carryable::printDescription(ostream & s) const
{
    s << description << '\n';
}

//-------------------------------------------------------------
/*
 * tells if it's a pack
 */
bool Carryable::isPack() const
{
    return false;
}

//-------------------------------------------------------------
/*
 * tells if it's edible
 */
bool Carryable::isEdible() const
{
    return false;
}

//-------------------------------------------------------------
/*
 * constructor
 */
Key::Key()
{
}

//-------------------------------------------------------------
/*
 * constructs key with value
 */
Key::Key( ID v )
{
    itemID = v;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Key::~Key()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Key::clone() const
{
    return new Key(*this);
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Key::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Key::input(istream & s, Map *m)
{
    s >> itemID >> name >> description;
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Key::save(ostream & s) const
{
    s << "key " << itemID << ' ' << name << ' ';
    description.save( s );
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Key::printDescription(ostream & s) const
{
    s << description << '\n';
}

//-------------------------------------------------------------
bool Key::operator == (const Key &v) const
{
    return itemID == v.itemID;
}

//-------------------------------------------------------------
/*
 * equality operators
 */
bool Key::operator != (const Key &v) const
{
    return itemID != v.itemID;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Treasure::~Treasure()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Treasure::clone() const
{
    return new Treasure(*this);
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Treasure::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Treasure::input(istream & s, Map *m)
{
    s >> itemID >> name >> description >> points >> weight >> size;

}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Treasure::save(ostream & s) const
{
    s << "treasure " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << points << ' ' << weight << ' ' << size;
}

//-------------------------------------------------------------
/*
 * returns gold value of item
 */
Gold Treasure::getPoints() const
{
    return points;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Treasure::printDescription(ostream & s) const
{
    s << description << '\n';
}

//-------------------------------------------------------------
/*
 * destructor
 */
Pack::~Pack()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Pack::clone() const
{
    Pack * temp = new Pack( *this );
    /*
    map<ID, Carryable *>::const_iterator iter;

    for ( iter = contents.begin(); iter != contents.end(); iter++ )
        temp->addItem( iter->second );
    */

    return temp;
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Pack::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Pack::input(istream & s, Map *m)
{
    s >> itemID >> name >> description >> weight >> size;
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Pack::save(ostream & s) const
{
    s << "pack " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << weight << ' ' << size;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Pack::printDescription( ostream & s ) const
{
    s << description << '\n';
}

/*
// adds item to the pack
void Pack::addItem( Carryable *v )
{
    contents[ v->getID() ] = v;
}

// drops item out of the pack
Item* Pack::dropItem( ID *v )
{
    if ( contents.count( *v ) )
    {
        Item *temp;
        temp = contents[ *v ];
        contents.erase( *v );
        return temp;
    }
    else
    {
        cout << *v << " does not exist.\n";
        return 0;
    }
}
*/

//-------------------------------------------------------------
/*
 * tells if it's a pack
 */
bool Pack::isPack() const
{
    return true;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Consumable::~Consumable()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Consumable::clone() const
{
    return new Consumable(*this);
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Consumable::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Consumable::input(istream & s, Map *m)
{
    s >> itemID >> name >> description >> health >> weight >> size;
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in
 * smae format in was input in.
 */
void Consumable::save(ostream & s) const
{
    s << "consumable " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << health << ' ' << weight << ' ' << size;
}

//-------------------------------------------------------------
/*
 * returns health value of item.  May
 * be negative
 */
int Consumable::getHealth() const
{
    return health;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Consumable::printDescription(ostream & s) const
{
    s << description << '\n';
}

//-------------------------------------------------------------
/*
 * tells if it's edible
 */
bool Consumable::isEdible() const
{
    return true;
}
