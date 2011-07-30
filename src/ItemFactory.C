/*
    A factory for producing (cloning) items. The items to be
    cloned should be added to its registry by the game.

    Tom Harada
*/

#include "ItemFactory.h"

#include "Item.h"

// ---------------------------------------------------------
// cleans up the prototype map
ItemFactory::~ItemFactory()
{
    map<string, Item *>::iterator iter = myPrototypes.begin();

    while ( iter != myPrototypes.end() )
    {
        delete iter->second;
        iter++;
    }
}

// ---------------------------------------------------------
// keys the given item pointer to the specified
// string in the prototype map
void ItemFactory::addItem( string key, Item * item )
{
    if ( myPrototypes.count( key ) )
        myPrototypes.erase( key );

    myPrototypes[ key ] = item;
}

// ---------------------------------------------------------
// returns a pointer to a fresh item of the
// specified type
Item * ItemFactory::generate( const string& type )
{
    if ( myPrototypes.count( type ) )
        return myPrototypes[ type ]->clone();
    else
        return 0;
}

// ---------------------------------------------------------
// writes the prototype list to the stream
void ItemFactory::save( ostream& s ) const
{
    map<string, Item *>::const_iterator iter = myPrototypes.begin();

    while ( iter != myPrototypes.end() )
    {
        iter->second->save( s );
        s << "\n";
        iter++;
    }
}

// ---------------------------------------------------------
// reads the prototype list from stream
void ItemFactory::input( istream& s )
{
    // to be implemented later
}

// ---------------------------------------------------------
// outputs using save operation
ostream& operator << ( ostream& s, const ItemFactory fac )
{
    fac.save( s );
    return s;
}

// ---------------------------------------------------------
// inputs using named input operation
istream& operator >> ( istream& s, ItemFactory fac )
{
    fac.input( s );
    return s;
}
