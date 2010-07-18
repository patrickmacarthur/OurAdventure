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
#include "Lock.h"
#include "LockState.h"
#include "Container.h"
#include "Map.h"

//-------------------------------------------------------------
/*
 * constructor
 */
Container::Container()
{
    myState = 0;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Container::~Container()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Container::clone() const
{
    Container * temp = new Container(*this);
    //ap<ID, Item *>::const_iterator iter;

    /*
    for ( iter = contents.begin(); iter != contents.end(); iter++ )
        temp->addItem( iter->second );
    */
    temp->setState( myState );
    return temp;
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Container::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    cout << "Container added to map\n";
}

//-------------------------------------------------------------
/*
 * adds Carryable to the container
 */
void Container::addItem( Carryable *v )
{
    carry[ v->getID() ] = v;
}

//-------------------------------------------------------------
/*
 * adds Container to the container
 */
void Container::addItem( Container *v )
{
    contain[ v->getID() ] = v;
}

//-------------------------------------------------------------
/*
 * return true and removes item if there
 * return false if closed or not there
 */
bool Container::getItem( const Carryable *v )
{
    if ( myState->isOpen() )
    {
        if ( carry.count( v->getID() ) )
        {
            carry.erase( v->getID() );
            return true;
        }
        else
        {
            map<ID, Container *>::iterator iter;

            for ( iter = contain.begin(); iter != contain.end(); iter++ )
            {
                if ( iter->second->isOpen() && iter->second->getItem( v ) )
                    return true;
            }

            return false;
        }
    }
    else
        return false;
}

//-------------------------------------------------------------
/*
 * returns if the container's open
 */
bool Container::isOpen() const
{
    return myState->isOpen();
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Container::input(istream & s, Map *m)
{
    /*
    string state;
    ID temp;

    s >> itemID >> name >> description >> state >> numItems;

    myState = LockStateFactory::generate( state );

    for ( int i = 0; i < numItems; i++ )
    {
        s >> temp;
        contents[ temp ] = 0;
    }
    */
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in same format in was
 * input in.
 */
void Container::save(ostream & s) const
{
    /*
    map<ID, Item *>::const_iterator iter;

    s << "container " << itemID << ' ' << name << ' ' << description
    << ' ' << *myState << numItems;

    for ( iter = contents.begin(); iter != contents.end(); iter++ )
        s << ' ' << iter->first;
    */
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
void Container::printDescription(ostream & s) const
{
    s << description << '\n';

    if ( myState->isOpen() )
    {
        map<ID, Carryable *>::const_iterator carryIter;
        map<ID, Container *>::const_iterator containIter;

        s << name << " contains:\n";

        if ( carry.size() == 0 && contain.size() == 0 )
            cout << " nothing\n";

        for ( carryIter = carry.begin(); carryIter != carry.end(); carryIter++ )
        {
            s << "  ";
            carryIter->second->printName( s );
            s << '\n';
        }

        for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        {
            s << "  ";
            containIter->second->printName( s );
            s << '\n';
        }
    }
    else
        s << getName() << " is " << *myState << ".\n";
}

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool Container::unlock(Key *v)
{
    return true;
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
void Container::open()
{
    myState->open( this );
}

//-------------------------------------------------------------
/*
 * Sets the state of the door: open or closed.
 */
void Container::setState( LockState * state )
{
    //delete myState;
    myState = state;
}

//-------------------------------------------------------------
/*
 * returns true if has item
 */
bool Container::hasItem( const Item *v ) const
{
    if ( myState->isClosed() )
        return false;
    else if ( carry.count( v->getID() ) )
        return true;
    else
    {
        map<ID, Container *>::const_iterator containIter;

        for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        {
            if ( containIter->second->hasItem( v ) )
                return true;
        }

        return false;
    }
}

//-------------------------------------------------------------
/*
 * returns reference to map of contents
 */
const map<ID, Container *> & Container::getContainers() const
{
    return contain;
}

//-------------------------------------------------------------
/*
 * returns reference to map of contents
 */
const map<ID, Carryable *> & Container::getCarryables() const
{
    return carry;
}

//-------------------------------------------------------------
/*
 * returns true if has container
 */
Container * Container::getContainer( const Name &v ) const
{
    map<ID, Container*>::const_iterator iter;

    for ( iter = contain.begin(); iter != contain.end(); iter++ )
    {
        if ( iter->second->getName() == v )
            return iter->second;
        else if ( iter->second->isOpen() )
        {
            Container * inner = iter->second->getContainer( v );

            if ( inner )
                return inner;
        }
    }

    return 0;
}

//-------------------------------------------------------------
/*
 * constructor that assigns a lock to the chest
 */
Chest::Chest()
{
    lock = 0;
    myState = 0;
}

//-------------------------------------------------------------
/*
 * constructor that assigns a lock to the chest
 */
Chest::Chest( Lock *l )
{
    lock = l;
    myState = 0;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Chest::~Chest()
{
    delete lock;
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Chest::clone() const
{
    Chest * temp = new Chest(*this);
    //Lock * tempLock = new Lock;
    //LockState * tempState;
    /*
    map<ID, Carryable *>::const_iterator carryIter;
    map<ID, Container *>::const_iterator containIter;

    for ( carryIter = carry.begin(); carryIter != carry.end(); carryIter++ )
        temp->addItem( carryIter->second );

    for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        temp->addItem( containIter->second );
    */
    /*
    if ( myState->isLocked() )
        tempState = LockStateFactory::generate( "locked" );
    else if ( myState->isClosed() )
        tempState = LockStateFactory::generate( "closed" );
    else if ( myState->isOpen() )
        tempState = LockStateFactory::generate( "open" );
    else
        tempState = 0;
    */
    //temp->setState( tempState );
    temp->setState( myState );
    //tempLock->setKeyID( lock->getKeyID() );
    //temp->setLock( tempLock );
    return temp;
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Chest::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Chest::input(istream & s, Map *m)
{
    string state;
    ID tempID;
    Carryable * tempCarry = 0;
    Container * tempContain = 0;

    s >> itemID >> name >> description >> state >> numItems;

    myState = LockStateFactory::generate( state );

    for ( int i = 0; i < numItems; i++ )
    {
        s >> tempID;
        tempCarry = m->getCarryableItem( tempID );
        tempContain = m->getContainer( tempID );

        if ( tempCarry )
            carry[ tempID ] = tempCarry;

        if ( tempContain )
            contain[ tempID ] = tempContain;
    }

    s >> tempID;

    delete lock;
    lock = new Lock( tempID );
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in same format in was
 * input in.
 */
void Chest::save(ostream & s) const
{
    map<ID, Carryable *>::const_iterator carryIter;
    map<ID, Container *>::const_iterator containIter;

    s << "container chest " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << *myState << ' ' << numItems;

    for ( carryIter = carry.begin(); carryIter != carry.end(); carryIter++ )
        s << ' ' << carryIter->first;

    for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        s << ' ' << containIter->first;

    s << ' ' << lock->getKeyID();
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
/*
void Chest::printDescription(ostream & s) const
{
    s << description;
}
*/

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool Chest::unlock(Key *v)
{
    /*
        if not locked
            return true;
        else
            if lock.getKey != key
                cout << "Error"
            else
                mystate->unlock( key)
                return true;
    */
    return myState->unlock( this, v, lock );
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
void Chest::open()
{
    myState->open( this );
}

//-------------------------------------------------------------
/*
 * sets the lock
 */
//void Chest::setLock( Lock *l )
//{
//    delete lock;
//  lock = l;
//}

//--------------------------------------------------------------
/*
 * Copy constructor
 */
Chest::Chest( const Chest & v ):
    Container(v)
{
    if ( v.lock == 0 )
        lock = 0;
    else
        lock = new Lock( *v.lock );
}

//--------------------------------------------------------------
/*
 * Assignment operator
 */
Chest & Chest::operator = ( const Chest & v )
{
    if ( this != &v )
    {
        delete lock;

        if ( v.lock == 0 )
            lock = 0;
        else
            lock = new Lock( *v.lock );
    }

    return *this;
}

//-------------------------------------------------------------
/*
 * constructor
 */
Box::Box()
{
    myState = 0;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Box::~Box()
{
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Box::clone() const
{
    Box * temp = new Box(*this);
    //LockState * tempState;
    /*
    map<ID, Carryable *>::const_iterator carryIter;
    map<ID, Container *>::const_iterator containIter;

    for ( carryIter = carry.begin(); carryIter != carry.end(); carryIter++ )
        temp->addItem( carryIter->second );

    for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        temp->addItem( containIter->second );
    */
    /*
    if ( myState->isLocked() )
        tempState = LockStateFactory::generate( "locked" );
    else if ( myState->isClosed() )
        tempState = LockStateFactory::generate( "closed" );
    else if ( myState->isOpen() )
        tempState = LockStateFactory::generate( "open" );
    else
        tempState = 0;

    temp->setState( tempState );
    */
    temp->setState( myState );
    return temp;
}

//-------------------------------------------------------------
/*
 * adds item to map
 */
void Box::addToMap( Map *m )
{
    m->add( this );

    // remove this later
    //cout << itemID << " added to map\n";
}

//-------------------------------------------------------------
/*
 * inputs from input stream
 */
void Box::input(istream & s, Map *m)
{
    string state;
    ID tempID;
    Carryable * tempCarry = 0;
    Container * tempContain = 0;

    s >> itemID >> name >> description >> state >> numItems;

    myState = LockStateFactory::generate( state );

    for ( int i = 0; i < numItems; i++ )
    {
        s >> tempID;
        tempCarry = m->getCarryableItem( tempID );
        tempContain = m->getContainer( tempID );

        if ( tempCarry )
            carry[ tempID ] = tempCarry;

        if ( tempContain )
            contain[ tempID ] = tempContain;

    }
}

//-------------------------------------------------------------
/*
 * outputs to output stream.  Saves in same format in was
 * input in.
 */
void Box::save(ostream & s) const
{
    map<ID, Carryable *>::const_iterator carryIter;
    map<ID, Container *>::const_iterator containIter;

    s << "container box " << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << *myState << ' ' << numItems;

    for ( carryIter = carry.begin(); carryIter != carry.end(); carryIter++ )
        s << ' ' << carryIter->first;

    for ( containIter = contain.begin(); containIter != contain.end(); containIter++ )
        s << ' ' << containIter->first;
}

//-------------------------------------------------------------
/*
 * prints description of item to stream
 */
/*
void Box::printDescription(ostream & s) const
{
    s << description;
}
*/

//-------------------------------------------------------------
/*
 * unlocks item if locked
 */
bool Box::unlock(Key *v)
{
    cout << getName() << " is not locked.\n";
    return true;
}

//-------------------------------------------------------------
/*
 * opens item if unlocked
 */
void Box::open()
{
    myState->open( this );
}

