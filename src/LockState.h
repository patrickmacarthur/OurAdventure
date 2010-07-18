#ifndef LOCKSTATE_H
#define LOCKSTATE_H

/* Paul Rioux  4/9/10
 *
 * this hierarchy represents the various states of an item
 * lock.  The states an item can be in are locked, closed,
 * and open.
*/

#include <iostream>
#include <string>
using namespace std;

class Item;
class Lock;
class Key;

class LockState {

    public:

        virtual ~LockState(){};
            // destructor - virtual for hierarchy

        virtual bool unlock(Item *, Key *, Lock *);
            // unlocks item if locked

        virtual bool open(Item *);
            // opens item if unlocked

        virtual void output(ostream &s) const = 0;
            // outputs a state

        virtual bool isLocked() const;
        virtual bool isClosed() const;
        virtual bool isOpen() const;
            // returns a boolean based on the state

    protected:

        void changeState(Item * item, LockState * state);
            // changes lock state to specified state

};

class LockedState: public LockState {

    public:

        virtual ~LockedState();
            // destructor

        virtual bool unlock(Item *, Key *, Lock *);
            // unlocks item if locked

        virtual bool open(Item *);
            // opens item if unlocked

        virtual void output(ostream &s) const;
            // outputs a state

        virtual bool isLocked() const;
        virtual bool isClosed() const;
            // returns a boolean based on the state

};

class ClosedState: public LockState {

    public:

        virtual ~ClosedState();
            // destructor

        virtual bool unlock(Item *, Key *, Lock *);
            // unlocks item if locked

        virtual bool open(Item *);
            // opens item if unlocked

        virtual void output(ostream &s) const;
            // outputs a state

        virtual bool isClosed() const;
            // returns a boolean based on the state
};

class OpenState: public LockState {

    public:

        virtual ~OpenState();
            // destructor

        virtual bool unlock(Item *, Key *, Lock *);
            // unlocks item if locked

        virtual bool open(Item *);
            // opens item if unlocked

        virtual void output(ostream &s) const;
            // outputs a state

        virtual bool isOpen() const;
            // returns a boolean based on the state

};

class LockStateFactory {

    public:

        static LockState * generate(const string & tag);
            // returns state associated with tag
};

ostream & operator << (ostream & s, const LockState & v);
    // outputs using output operation above

#endif
