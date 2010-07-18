/*
    A class representing the adventurer. The adventurer's vital
    statistics are to be read from and written to files in
    the following format:

        healthLevel movesAtCurrentLevel numberItems weightItems
        itemId itemId ...
        currentFeatureId

    If one or more of the items is a pack, all of the
    adventurer's other items will be inside the largest pack.

    The adventurer has a set maximum health. Every 20 actions,
    his health level decreases by one and the amount of weight
    he may carry is decreased by 20% of a set maximum. If the
    adventurer is carrying more than currently allowed, he must
    drop items before he can interact with the environment. At
    health level 0, the game is over.

    Tom Harada
*/

#include "Adventurer.h"

#include "Inventory.h"
#include "Feature.h"
#include "Weight.h"
#include "Map.h"
#include "Carryable.h"

int Adventurer::myMaxHealth = 5;
int Adventurer::myMaxWeight = 30;
int Adventurer::myMaxMovesUntilHealthDrop = 20;

// ---------------------------------------------------------
// constructor takes pointer to map
Adventurer::Adventurer( Map * map )
{
    myMap = map;
    myInventory = 0;
}

// ---------------------------------------------------------
// destructor
Adventurer::~Adventurer()
{
    delete myInventory;
}

// ---------------------------------------------------------
// purges the inventory
void Adventurer::clear()
{
    delete myInventory;
}

// ---------------------------------------------------------
// reads adventurer's stats from stream
void Adventurer::input( istream& s )
{
    int numItems;
    int weight;
    map<ID, Carryable *> items;
    ID id;
    Carryable * item;
    Carryable * largestPack = 0;

    s >> myHealth;
    s >> myMovesUntilHealthDrop;
    s >> numItems >> weight;

    for ( int i = 0; i < numItems; i++ )
    {
        s >> id;
        item = myMap->getCarryableItem( id );
        items[ id ] = item;

        if ( item->isPack() && ( !largestPack ||
            item->getSize() > largestPack->getSize() ) )
            largestPack = item;
    }

    if ( largestPack )
    {
        setInventory( new PackStrategy( largestPack ) );

        map<ID, Carryable *>::iterator iter = items.begin();
        while ( iter != items.end() )
        {
            if ( iter->second != largestPack )
                myInventory->addItem( this, iter->second );

            iter++;
        }
    }
    else
    {
        setInventory( new HandStrategy );

        map<ID, Carryable *>::iterator iter = items.begin();
        while ( iter != items.end() )
        {
            myInventory->addItem( this, iter->second );
            iter++;
        }
    }

    s >> id;
    myCurrentFeature = myMap->getFeature( id );
    cout << "I am in ";
    myCurrentFeature->printName( cout );
    cout << ".\n\n";
}

// ---------------------------------------------------------
// writes adventurer's stats in game-readable form
void Adventurer::save( ostream& s ) const
{
    s << myHealth << " ";
    s << myMovesUntilHealthDrop << " ";
    s << myInventory->getCount() << " ";
    s << myInventory->getWeight() << "\n";
    s << *myInventory << "\n";
    s << myCurrentFeature->getID();
}

// ---------------------------------------------------------
// sets adventurer's health (up to the maximum)
void Adventurer::setHealth( const int v )
{
    if ( v > myMaxHealth )
    {
        myHealth = myMaxHealth;
        myMovesUntilHealthDrop = myMaxMovesUntilHealthDrop;
    }
    else if ( v < 0 )
        myHealth = 0;
    else
    {
        myHealth = v;
        myMovesUntilHealthDrop = myMaxMovesUntilHealthDrop;
    }
}

// ---------------------------------------------------------
// returns adventurer's health
int Adventurer::getHealth() const
{
    return myHealth;
}

// ---------------------------------------------------------
// returns moves left until health drop
int Adventurer::getMovesLeft() const
{
    return myMovesUntilHealthDrop;
}

// sets moves left until health drop
void Adventurer::setMovesLeft( int v )
{
    myMovesUntilHealthDrop = v;
}

// ---------------------------------------------------------
// registers one move or action; adventurer's
// health will decrease every 20 actions
int Adventurer::move()
{
    myMovesUntilHealthDrop--;

    if ( myMovesUntilHealthDrop < 1 )
    {
        myMovesUntilHealthDrop = myMaxMovesUntilHealthDrop;
        setHealth( myHealth - 1 );
        
        switch ( myHealth )
        {
            case averageHealth:
                cout << "I'm starting to feel hungry.\n";
                break;
            case poorHealth:
                cout << "I'm getting really hungry.\n";
                break;
            case dyingHealth:
                cout << "I'm starving here!\n";
                break;
        }
    }
        
    cout << "\n";

    return myHealth;
}

// ---------------------------------------------------------
// returns the amount of weight the adventurer
// is currently able to carry, which varies
// depending on health and determines whether
// items must be dropped before adventurer can
// do anything else
Weight Adventurer::getStrength() const
{
    switch ( myHealth )
    {
        case highHealth:
        case goodHealth:
            return myMaxWeight;
        case averageHealth:
            return myMaxWeight * 0.8f;
        case poorHealth:
            return myMaxWeight * 0.2f;
        case dyingHealth:
            return 0;
        default:
            // Should not reach here
            return -1;
    }
}

// ---------------------------------------------------------
// Returns true if the adventurer is alive.
bool Adventurer::isAlive() const
{
    return myHealth > 0;
}


// ---------------------------------------------------------
// returns a pointer to the inventory
Inventory * Adventurer::getInventory()
{
    return myInventory;
}

// ---------------------------------------------------------
// sets the inventory. Used to change between
// hands and pack.
void Adventurer::setInventory( Inventory * inv )
{
    if ( myInventory != inv )
    {
        delete myInventory;
        myInventory = inv;
    }
}

// ---------------------------------------------------------
// returns pointer to current feature
Feature * Adventurer::getCurrentFeature() const
{
    return myCurrentFeature;
}

// ---------------------------------------------------------
// moves to specified feature
void Adventurer::setCurrentFeature( Feature * feat )
{
    myCurrentFeature = feat;
}

// ---------------------------------------------------------
// returns the previous direction
Direction Adventurer::getPreviousDirection() const
{
    return myPreviousDirection;
}

// ---------------------------------------------------------
// sets the previous direction
void Adventurer::setPreviousDirection( const Direction& dir )
{
    myPreviousDirection = dir;
}
