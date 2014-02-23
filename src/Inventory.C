/*
    Abstract class representing the adventurer's inventory.
    Child classes are responsible for the mechanics of
    storage, while game commands should implement switching
    between storage strategies and basically all inventory
    manipulation tasks.

    Tom Harada
*/

#include "Inventory.h"

#include "Carryable.h"
#include "ID.h"
#include "Weight.h"
#include "Name.h"
#include "Adventurer.h"

// ---------------------------------------------------------
// outputs using named out operator
ostream& operator << ( ostream& s, const Inventory& inv )
{
    inv.output( s );
    return s;
}

/*
    A storage strategy comprising two hands, each of which
    may hold something.
*/

// ---------------------------------------------------------
// constructor sets both hands to empty
HandStrategy::HandStrategy()
{
    myLeftHand = 0;
    myRightHand = 0;
}

// ---------------------------------------------------------
// attempts to pick up the item with a free hand
bool HandStrategy::addItem( Adventurer * adv, Carryable * item )
{
    if ( item->isPack() )
    {
        Size total;

        if ( myLeftHand )
            total += myLeftHand->getSize();

        if ( myRightHand )
            total += myRightHand->getSize();

        if ( total > item->getSize() )
        {
            cout << "Try dropping some items first.\n";
            return false;
        }
        else
        {
            PackStrategy * pack = new PackStrategy( item );

            if ( myLeftHand )
                pack->addItem( 0, myLeftHand );

            if ( myRightHand )
                pack->addItem( 0, myRightHand );

            adv->setInventory( pack );

            return true;
        }
    }
    else
    {
        if ( !myLeftHand )
            myLeftHand = item;
        else if ( !myRightHand )
            myRightHand = item;
        else
            return false;
    }

    return true;
}

// ---------------------------------------------------------
// removes the item from the hand carrying it
bool HandStrategy::removeItem( Adventurer * adv, const Name& name )
{
    if ( myLeftHand && myLeftHand->getName() == name )
        myLeftHand = 0;
    else if ( myRightHand && myRightHand->getName() == name )
        myRightHand = 0;
    else
        return false;

    return true;
}

// ---------------------------------------------------------
// returns whether or not inventory contains
// item with given name
bool HandStrategy::hasItem( const Name& name )
{
    return ( ( myLeftHand && myLeftHand->getName() == name ) ||
        ( myRightHand && myRightHand->getName() == name ) );
}

// ---------------------------------------------------------
// returns the total weight of everything in the
// inventory
Weight HandStrategy::getWeight() const
{
    Weight total;

    if ( myLeftHand )
        total += myLeftHand->getWeight();

    if ( myRightHand )
        total += myRightHand->getWeight();

    return total;
}

// ---------------------------------------------------------
// returns pointer to item
Carryable * HandStrategy::getItem( const Name& name )
{
    if ( myLeftHand && myLeftHand->getName() == name )
        return myLeftHand;
    else if ( myRightHand && myRightHand->getName() == name )
        return myRightHand;
    else
        return 0;
}

// ---------------------------------------------------------
// returns the number of items in the inventory
int HandStrategy::getCount() const
{
    return ( myLeftHand != 0 ) + ( myRightHand != 0 );
}

// ---------------------------------------------------------
// lists names of items in the inventory
void HandStrategy::list( ostream& s ) const
{
    if ( !myLeftHand && !myRightHand )
        cout << "My inventory is empty.";
    else
    {
        cout << "I am carrying:";

        if ( myLeftHand )
            cout << "\n  " << myLeftHand->getName();

        if ( myRightHand )
            cout << "\n  " << myRightHand->getName();
    }
}

// ---------------------------------------------------------
// outputs items to the stream
void HandStrategy::output( ostream& s ) const
{
    if ( myLeftHand )
        s << myLeftHand->getID() << " ";

    if ( myRightHand )
        s << myRightHand->getID();
}

/*
    A storage strategy comprising a pack, which may hold
    multiple items.
*/

// ---------------------------------------------------------
// constructor takes pointer to pack
PackStrategy::PackStrategy( Carryable * pack )
{
    myPack = pack;
}

// ---------------------------------------------------------
// attempts to pick up the item and put it in
// the pack
bool PackStrategy::addItem( Adventurer * adv, Carryable * item )
{
    Size total;

    map<Name, Carryable *>::iterator iter = myContents.begin();
    while ( iter != myContents.end() )
    {
        total += iter->second->getSize();
        ++iter;
    }

    if ( item->isPack() && item->getSize() > myPack->getSize() )
    {
        if ( total + myPack->getSize() > item->getSize() )
        {
            return false;
        }
        else
        {
            myContents[ myPack->getName() ] = myPack;
            myPack = item;
        }
    }
    else
    {
        if ( item->getSize() + total > myPack->getSize() )
            return false;

        myContents[ item->getName() ] = item;
    }

    return true;
}

// ---------------------------------------------------------
// removes the item from the pack
bool PackStrategy::removeItem( Adventurer * adv, const Name& name )
{
    if ( name == myPack->getName() )
    {
        if ( myContents.begin() != myContents.end() )
        {
            cout << "My pack is not empty!\n\n";
            return false;
        }
        else
        {
            adv->setInventory( new HandStrategy );
            return true;
        }
    }
    else
    {
        if ( !myContents.count( name ) )
        {
            cout << "I don't have " << name << "!\n\n";
            return false;
        }
        else
        {
            myContents.erase( name );
            return true;
        }
    }
}

// ---------------------------------------------------------
// returns whether or not inventory contains
// item with given name
bool PackStrategy::hasItem( const Name& name )
{
    return myContents.count( name );
}

// ---------------------------------------------------------
// returns pointer to item
Carryable * PackStrategy::getItem( const Name& name )
{
    if ( myContents.count( name ) )
        return myContents[ name ];
    else if ( myPack->getName() == name )
        return myPack;
    else
        return 0;
}

// ---------------------------------------------------------
// returns the total weight of everything in the
// inventory
Weight PackStrategy::getWeight() const
{
    Weight total;

    total += myPack->getWeight();

    map<Name, Carryable *>::const_iterator iter = myContents.begin();
    while ( iter != myContents.end() )
    {
        total += iter->second->getWeight();
        ++iter;
    }

    return total;
}

// ---------------------------------------------------------
// returns the number of items in the inventory
int PackStrategy::getCount() const
{
    int total = 0;

    map<Name, Carryable *>::const_iterator iter = myContents.begin();
    while ( iter != myContents.end() )
    {
        ++total;
        ++iter;
    }

    return total + 1;
}

// ---------------------------------------------------------
// lists names of items in the inventory
void PackStrategy::list( ostream& s ) const
{
    cout << "I am carrying: ";
    cout << "\n  " << myPack->getName();

    map<Name, Carryable *>::const_iterator iter = myContents.begin();
    while ( iter != myContents.end() )
    {
        cout << "\n    " << iter->first;
        ++iter;
    }
}

// ---------------------------------------------------------
// outputs items to the stream
void PackStrategy::output( ostream& s ) const
{
    map<Name, Carryable *>::const_iterator iter = myContents.begin();

    s << myPack->getID();

    while ( iter != myContents.end() )
    {
        s << " " << iter->second->getID();
        ++iter;
    }
}
