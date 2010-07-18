#ifndef ITEM_H
#define ITEM_H

/* Paul Rioux  4/9/10
 *
 * this class defines an item to be found in a
 * dungeon.  It may be input and output as well
 * as cloned.
 */

#include <iostream>
#include <string>
using namespace std;
#include "Description.h"
#include "ID.h"
#include "Name.h"

class Map;
class LockState;

class Item{

    public:

        virtual ~Item();
            // destructor

        virtual Item * clone() const = 0;
            // dynamic copy

        virtual void addToMap(Map *) = 0;
            // adds item to map

        virtual void  input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        void printName(ostream & s) const;
            // prints name of item to stream

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

        const ID& getID() const;
            // returns a constant reference to ID

        const Name& getName() const;
            // returns a constant reference to Name

    protected:

        ID itemID;
        Name name;
        Description description;

        friend class LockState;

        virtual void setState( LockState * state );
            // Sets the state of the door: open or closed.

};

//istream & operator >> (istream & s, Item & v);
    // outputs using named operation

ostream & operator << (ostream & s, const Item & v);
    // outputs using named operation

#endif
