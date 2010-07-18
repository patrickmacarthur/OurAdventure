/* Paul Rioux  4/9/10
 *
 * this hierarchy represents the various states of an item
 * lock.  The states an item can be in are locked, closed,
 * and open.
*/

#include <iostream>
#include <string>
using namespace std;
#include "Item.h"
#include "LockState.h"
#include "Lock.h"
#include "Carryable.h"

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool LockState::unlock(Item *v, Key *k, Lock *l)
{
    cout << "I am unable to unlock " << v->getName() << ".\n\n";
    return false;
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
bool LockState::open(Item * v)
{
    cout << "I am unable to open " << v->getName() << ".\n\n";

    return false;
}

//-------------------------------------------------------------
/*
 * changes lock state to specified state
 */
void LockState::changeState(Item * item, LockState * state)
{
    item->setState( state );
}

//-------------------------------------------------------------
/*
 * eturns a boolean based on the state
 */
bool LockState::isLocked() const
{
    return false;
}

bool LockState::isClosed() const
{
    return false;
}

bool LockState::isOpen() const
{
    return false;
}

//-------------------------------------------------------------
/*
 * destructor
 */
LockedState::~LockedState()
{
}

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool LockedState::unlock(Item * v, Key *k, Lock *l)
{
    if ( l->getKeyID() == k->getID() )
    {
        changeState( v, LockStateFactory::generate( "closed" ) );
        cout << v->getName() << " is unlocked.\n";
        return true;
    }
    else
    {
        cout << "Wrong key!\n";
        return false;
    }
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
bool LockedState::open(Item * v)
{
    cout << v->getName() << " is locked.\n";

    return false;
}

//-------------------------------------------------------------
/*
 * outputs a state
 */
void LockedState::output(ostream &s) const
{
    s << "locked";
}

//-------------------------------------------------------------
/*
 * eturns a boolean based on the state
 */
bool LockedState::isLocked() const
{
    return true;
}

bool LockedState::isClosed() const
{
    return true;
}

//-------------------------------------------------------------
/*
 * destructor
 */
ClosedState::~ClosedState()
{
}

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool ClosedState::unlock(Item * v, Key *k, Lock *l)
{
    cout << v->getName() << " is already unlocked.\n";
    return false;
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
bool ClosedState::open(Item * v)
{
    changeState( v, LockStateFactory::generate( "open" ) );
    cout << v->getName() << " opened.\n";

    return true;
}

//-------------------------------------------------------------
/*
 * outputs a state
 */
void ClosedState::output(ostream &s) const
{
    s << "closed";
}

//-------------------------------------------------------------
/*
 * eturns a boolean based on the state
 */
bool ClosedState::isClosed() const
{
    return true;
}

//-------------------------------------------------------------
/*
 * destructor
 */
OpenState::~OpenState()
{
}

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool OpenState::unlock(Item * v, Key *k, Lock *l)
{
    cout << v->getName() << " is already unlocked.\n";
    return false;
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
bool OpenState::open(Item * v)
{
    cout << v->getName() << " is already open.\n";

    return false;
}

//-------------------------------------------------------------
/*
 * outputs a state
 */
void OpenState::output(ostream &s) const
{
    s << "open";
}

//-------------------------------------------------------------
/*
 * eturns a boolean based on the state
 */
bool OpenState::isOpen() const
{
    return true;
}

//-------------------------------------------------------------
/*
 * returns state associated with tag
 */
LockState * LockStateFactory::generate( const string & tag )
{
    static LockedState lock;
    static ClosedState closed;
    static OpenState opened;

    if ( tag == "locked" )
        return &lock;
    else if ( tag == "closed" )
        return &closed;
    else if ( tag == "open" )
        return &opened;
    else
        return 0;
}

//-------------------------------------------------------------
/*
 * outputs using output operation above
 */
ostream & operator << (ostream & s, const LockState & v)
{
    v.output( s );
    return s;
}
