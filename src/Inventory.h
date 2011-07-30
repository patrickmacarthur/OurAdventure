#ifndef INVENTORY_H
#define INVENTORY_H

/*
    Abstract class representing the adventurer's inventory.
    Child classes are responsible for the mechanics of
    storage, while game commands should implement switching
    between storage strategies and basically all inventory
    manipulation tasks.

    Input and output should be in the following form:

        numberItems weightItems
        itemId itemId ...

    Tom Harada
*/

#include <iostream>
#include <map>
using namespace std;

class Carryable;
class Pack;
class ID;
class Weight;
class Name;
class Adventurer;

class Inventory {
    public:
        virtual ~Inventory(){};
            // destructor

        virtual bool addItem( Adventurer * adv, Carryable * item ) = 0;
            // attempts to add a pointer to the given item
            // to the player's inventory; returns success
            // or failure; takes pointer to adventurer

        virtual bool removeItem( Adventurer * adv, const Name& name ) = 0;
            // attempts to delete the given item's pointer
            // from the player's inventory; returns success
            // or failure; takes pointer to adventurer

        virtual bool hasItem( const Name& name ) = 0;
            // returns whether or not inventory contains
            // item with given name

        virtual Carryable * getItem( const Name& name ) = 0;
            // returns pointer to item

        virtual Weight getWeight() const = 0;
            // returns the total weight of everything in the
            // inventory

        virtual int getCount() const = 0;
            // returns the number of items in the inventory

        virtual void output( ostream& s ) const = 0;
            // outputs items to the stream

        virtual void list( ostream& s ) const = 0;
            // lists names of items in the inventory
};

ostream& operator << ( ostream& s, const Inventory& inv );
    // outputs using named output operator

/*
    A storage strategy comprising two hands, each of which
    may hold something.
*/

class HandStrategy: public Inventory {
    public:
        HandStrategy();
            // constructor sets both hands to empty

        virtual bool addItem( Adventurer * adv, Carryable * item );
            // attempts to pick up the item with a free hand;
            // takes pointer to adventurer

        virtual bool removeItem( Adventurer * adv, const Name& name );
            // attempts to delete the given item's pointer
            // from the player's inventory; returns success
            // or failure; takes pointer to adventurer

        virtual bool hasItem( const Name& name );
            // returns whether or not inventory contains
            // item with given ID

        virtual Carryable * getItem( const Name& name );
            // returns pointer to item

        virtual Weight getWeight() const;
            // returns the total weight of everything in the
            // inventory

        virtual int getCount() const;
            // returns the number of items in the inventory

        virtual void output( ostream& s ) const;
            // outputs items to the stream

        virtual void list( ostream& s ) const;
            // lists names of items in the inventory

    private:
        Carryable * myLeftHand;
        Carryable * myRightHand;
};

/*
    A storage strategy comprising a pack, which may hold
    multiple items.
*/

class PackStrategy: public Inventory {
    public:
        PackStrategy( Carryable * pack );
            // constructor takes pointer to pack

        virtual bool addItem( Adventurer * adv, Carryable * item );
            // attempts to pick up the item and put it in
            // the pack; takes pointer to adventurer

        virtual bool removeItem( Adventurer * adv, const Name& name );
            // attempts to delete the given item's pointer
            // from the player's inventory; returns success
            // or failure; takes pointer to adventurer

        virtual bool hasItem( const Name& name );
            // returns whether or not inventory contains
            // item with given name

        virtual Weight getWeight() const;
            // returns the total weight of everything in the
            // inventory

        virtual Carryable * getItem( const Name& name );
            // returns pointer to item

        virtual int getCount() const;
            // returns the number of items in the inventory

        virtual void output( ostream& s ) const;
            // outputs items to the stream

        virtual void list( ostream& s ) const;
            // lists names of items in the inventory

    private:
        Carryable * myPack;
        map<Name, Carryable *> myContents;
};

#endif
