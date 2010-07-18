#ifndef CONTAINER_H
#define CONTAINER_H

/* Paul Rioux  4/9/10
 *
 * this class defines an item which can be locked
 * or opened.  This would include chests and boxes.
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "Item.h"

class Lock;
class LockState;
class Map;

class Container: public Item {

    public:

        Container();
            // constructor

        virtual ~Container();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        void addItem(Carryable *);
            // adds Carryable to the container

        void addItem(Container *);
            // adds Container to the container

        bool getItem(const Carryable *);
            // return true and removes item if there
            // return false if closed or not there

        bool isOpen() const;
            // returns if the container's open

        virtual void  input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        virtual void printDescription(ostream & s) const;
            // prints description of item to stream

        virtual bool unlock(Key *);
            // unlocks item if locked

        virtual void open();
            // opens item if unlocked

        virtual bool hasItem(const Item *) const;
            // returns true if has item

        const map<ID, Container *> & getContainers() const;
            // returns reference to map of contents

        const map<ID, Carryable *> & getCarryables() const;
            // returns reference to map of contents

        Container * getContainer(const Name &v) const;
            // returns true if has container

    protected:

        LockState *myState;
        int numItems;
        map<ID, Carryable *> carry;
        map<ID, Container *> contain;

        virtual void setState( LockState * state );
            // Sets the state of the door: open or closed.

};

class Chest: public Container {

    public:

        Chest();
            // constructor

        Chest(Lock*);
            // constructor that assigns a lock
            // to the chest

        virtual ~Chest();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void  input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        /*
        virtual void printDescription(ostream & s) const;
            // prints description of item to stream
         */

        virtual bool unlock(Key *);
            // unlocks item if locked

        virtual void open();
            // opens item if unlocked

        void setLock(Lock*);
            // sets the lock

    protected:

        Chest( const Chest & );
            // copy constructor

        Chest & operator = ( const Chest & );
            // assignment operator

    private:

        Lock *lock;

};

class Box: public Container {

    public:

        Box();
            // constructor

        virtual ~Box();
            // destructor

        virtual Item * clone() const;
            // dynamic copy

        virtual void addToMap(Map *);
            // adds item to map

        virtual void  input(istream & s, Map *m);
            // inputs from input stream

        virtual void save(ostream & s) const;
            // outputs to output stream.  Saves in
            // smae format in was input in.

        /*
        virtual void printDescription(ostream & s) const;
            // prints description of item to stream
         */

        virtual bool unlock(Key *);
            // unlocks item if locked

        virtual void open();
            // opens item if unlocked

};

#endif
