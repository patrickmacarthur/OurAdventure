#ifndef CARRYABLE_H
#define CARRYABLE_H

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
#include "Item.h"
#include "Gold.h"
#include "Weight.h"
#include "Size.h"

class Map;

class Carryable: public Item {

    public:

        virtual ~Carryable();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual Weight getWeight() const;
            // returns weight of item

        virtual Size getSize() const;
            // returns size of item

        virtual Gold getPoints() const;
            // returns gold value of item

        virtual int getHealth() const;
            // returns health value of item.  May
            // be negative

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

        virtual bool isPack() const;
            // tells if it's a pack

        virtual bool isEdible() const;
            // tells if it's edible

    protected:

        Size size;
        Weight weight;

};

class Key: public Carryable {

    public:

        Key();
            // constructor

        Key(ID);
            // constructs key with value

        virtual ~Key();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

        bool operator == (const Key &v) const;
        bool operator != (const Key &v) const;
            // equality operators

};

class Treasure: public Carryable {

    public:

        virtual ~Treasure();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual Gold getPoints() const;
            // returns gold value of item

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

    private:

        Gold points;

};

class Pack: public Carryable {

    public:

        virtual ~Pack();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream
    /*
        void addItem(Carryable *v);
            // adds item to the pack

        Item* dropItem(ID *v);
            // drops item out of the pack
    */

        virtual bool isPack() const;
            // tells if it's a pack

    /*
    private:

        map<ID, Carryable *> contents;
    */

};

class Consumable: public Carryable {

    public:

        Consumable() { health = 0; }

        virtual ~Consumable();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual int getHealth() const;
            // returns health value of item.  May
            // be negative

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

        virtual bool isEdible() const;
            // tells if it's edible

    private:

        int health;

};

#endif
