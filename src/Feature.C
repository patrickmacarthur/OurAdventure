/* Feature.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include "Feature.h"

#include <cstdlib>

#include "Adjacency.h"
#include "Carryable.h"
#include "Container.h"
#include "ID.h"
#include "Lock.h"
#include "LockState.h"
#include "Map.h"

/*
 * The Feature class represents a feature (room, passage, or
 * doorway) in the dungeon.  All features have exits that may be
 * queried for.  Some features may have items on the floor; these
 * may be taken (removed), queried, and more may be dropped
 * (added) if the feature allows items.  The feature and
 * adjacency list may be input and saved.
 */

//-------------------------------------------------------------
/*
 * default constructor
 */
Feature::Feature()
{
    m_exits = 0;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Feature::~Feature()
{
    delete m_exits;
}

//-------------------------------------------------------------
/*
 * Adds an item to the feature.  Returns false if the
 * item cannot be dropped in this feature for whatever
 * reason.
 */
bool Feature::addItem( Carryable * item )
{
    return false;
}

//-------------------------------------------------------------
/*
 * Adds this item to the map
 */
void Feature::addToMap( Map * map )
{
    map->add( this );
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Feature::clone() const
{
    return new Feature(*this);
}

//-------------------------------------------------------------
/*
 * Returns the carryable item in the feature with the given name.
 * If there is no carryable item in the feature, return false.
 */
Carryable * Feature::getCarryableItem( const Name & name )
{
    return 0;
}

//-------------------------------------------------------------
/*
 * Returns the container in the feature with the given name.  If
 * there is no container in the feature, return false.
 */
Container * Feature::getContainer( const Name & name )
{
    return 0;
}

//-------------------------------------------------------------
/*
 * Returns the exit from the given direction.  Returns
 * 0 if there is no feature in that direction.
 */
Feature * Feature::getExit( const Direction & v ) const
{
    return m_exits->getExit( v );
}

//-------------------------------------------------------------
/*
 * Returns a list of items in the feature.  If there
 * are no items, returns an empty list.
 */
std::list<Item *> Feature::getItems() const
{
    return std::list<Item *>();
}

//-------------------------------------------------------------
/*
 * Returns the total score of all items in this room.
 */
Gold Feature::getPoints() const
{
    return 0;
}

//-------------------------------------------------------------
/*
 * Returns true if the item is in this feature
 */
bool Feature::hasItem( const Item * v ) const
{
    return false;
}

//-------------------------------------------------------------
/*
 * Returns true if this is a doorway and it is closed.
 */
bool Feature::isClosed() const
{
    return false;
}

//-------------------------------------------------------------
/*
 * Returns true if this is a doorway and it is locked.
 */
bool Feature::isLocked() const
{
    return false;
}

//-------------------------------------------------------------
/*
 * Returns true if this is not a doorway or it is open.
 */
bool Feature::isOpen() const
{
    return true;
}

//-------------------------------------------------------------
/*
 * Opens the door if this happens to be a doorway.
 * Returns false if this can't be done.
 */
bool Feature::openDoor()
{
    std::cout << "There is no door here.\n";
    return false;
}

//--------------------------------------------------------------
/*
 * Sets the exits from this room.
 */
void Feature::setExits( Adjacency * v )
{
    m_exits = v;
}

//-------------------------------------------------------------
/*
 * Unlocks the door with the given key if this happens
 * to be a doorway.  Returns false if this can't be
 * done.
 */
bool Feature::unlockDoor( Key * key )
{
    std::cout << "There is no door here.\n";
    return false;
}

//-------------------------------------------------------------
/*
 * Removes a carryable item from the feature.  Returns false if
 * the item cannot be removed from this feature for whatever
 * reason.
 */
bool Feature::removeItem( const Carryable * item )
{
    return false;
}

//-------------------------------------------------------------
/*
 * Saves the feature to the specified stream.  Meant
 * for writing to disk.
 */
void Feature::save( std::ostream & s )
{
    s << "feature ";
}

//-------------------------------------------------------------
/*
 * Saves the exits from this feature to the specified stream.
 * Meant for writing to disk.
 */
void Feature::saveExits( std::ostream & s )
{
    m_exits->save( s );
}

//--------------------------------------------------------------
/*
 * Copy constructor
 */
Feature::Feature( const Feature & v )
{
    if ( v.m_exits == 0 )
    {
        m_exits = 0;
    }
    else
    {
        m_exits = dynamic_cast<Adjacency*>( v.m_exits->clone() );
    }
}

//--------------------------------------------------------------
/*
 * Assignment operator
 */
Feature & Feature::operator = ( const Feature & v )
{
    if ( this != &v )
    {
        delete m_exits;

        if ( v.m_exits == 0 )
        {
            m_exits = 0;
        }
        else
        {
            m_exits = dynamic_cast<Adjacency*>( v.m_exits->clone() );
        }
    }

    return *this;
}

//==============================================================
/*
 * The Room class represents a room in the dungeon that can have
 * any number of exits and items on the floor.
 */

//-------------------------------------------------------------
/*
 * destructor
 */
Room::~Room()
{
}

//-------------------------------------------------------------
/*
 * Adds an item to the feature.  Returns false if the
 * item cannot be dropped in this feature for whatever
 * reason.
 */
bool Room::addItem( Carryable * v )
{
    m_carryables.insert( std::pair<ID, Carryable*>(
                v->getID(), v ) );
    return true;
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Room::clone() const
{
    return new Room(*this);
}

//-------------------------------------------------------------
/*
 * Returns the carryable item in the feature with the given name.
 * If there is no carryable item in the feature, return false.
 */
Carryable * Room::getCarryableItem( const Name & name )
{
    std::map<ID, Carryable *>::iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        if ( iter->second->getName() == name )
        {
            return iter->second;
        }
    }

    return 0;
}

//-------------------------------------------------------------
/*
 * Returns the container in the feature with the given name.  If
 * there is no container in the feature, return false.
 */
Container * Room::getContainer( const Name & name )
{
    std::map<ID, Container *>::iterator iter;
    for ( iter = m_containers.begin();
            iter != m_containers.end(); ++iter )
    {
        if ( iter->second->getName() == name )
        {
            return iter->second;
        }
        else if ( iter->second->isOpen() )
        {
            Container * inner = iter->second->getContainer( name );
            if ( inner )
            {
                return inner;
            }
        }
    }

    return 0;
}

//-------------------------------------------------------------
/*
 * Returns a list of items in the feature.  If there
 * are no items, returns an empty list.
 */
std::list<Item *> Room::getItems() const
{
    std::list<Item *> list;

    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        list.push_back( iter->second );
    }
    std::map<ID, Container *>::const_iterator iter2;
    for ( iter2 = m_containers.begin();
            iter2 != m_containers.end(); ++iter2 )
    {
        list.push_back( iter2->second );
    }

    return list;
}

//-------------------------------------------------------------
/*
 * Returns the total score of all items in this room.
 */
Gold Room::getPoints() const
{
    Gold score;

    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        score += iter->second->getPoints();
    }

    return score;
}

//-------------------------------------------------------------
/*
 * Returns true if the item is in this feature
 */
bool Room::hasItem( const Item * v ) const
{
    ID id = v->getID();

    if ( m_carryables.count( id ) > 0 )
    {
        return true;
    }
    else if ( m_containers.count( id ) > 0 )
    {
        return true;
    }
    else
    {
        std::map<ID, Container *>::const_iterator iter;
        for ( iter = m_containers.begin();
                iter != m_containers.end(); ++iter )
        {
            if ( iter->second->hasItem( v ) )
            {
                return true;
            }
        }

        return false;
    }
}

//-------------------------------------------------------------
/*
 * Removes a carryable item from the feature.  Returns false if
 * the item cannot be removed from this feature for whatever
 * reason.
 */
bool Room::removeItem( const Carryable * item )
{
    if ( m_carryables.erase( item->getID() ) == 1 )
    {
        return true;
    }
    else
    {
        std::map<ID, Container *>::iterator iter;
        for ( iter = m_containers.begin();
                iter != m_containers.end(); ++iter )
        {
            if ( iter->second->getItem( item ) )
            {
                return true;
            }
        }
    }

    return false;
}

//-------------------------------------------------------------
/*
 * Inputs the feature
 */
void Room::input( std::istream & s, Map * map )
{
    int count;
    ID id;
    Item::input( s, map );

    s >> count;
    for ( int i = 0; i < count; ++i )
    {
        s >> id;
        if ( map->getCarryableItem( id ) )
        {
            m_carryables[ id ] = map->getCarryableItem( id );
        }
        else if ( map->getContainer( id ) )
        {
            m_containers[ id ] = map->getContainer( id );
        }
        else
        {
            std::cerr << "Parse warning: No such id " << id
                      << " in feature " << this->getID() << '\n';
        }
    }
}

//-------------------------------------------------------------
/*
 * Outputs a detailed description of the feature and
 * all items within
 */
void Room::printDescription( std::ostream & s ) const
{
    Item::printDescription( s );

    printItems( s );
}

//-------------------------------------------------------------
/*
 * Saves the feature to the specified stream.  Meant
 * for writing to disk.
 */
void Room::save( std::ostream & s )
{
    Feature::save( s );
    s << "room ";
    s << itemID << ' ' << name << ' ';
    description.save( s );

    saveItemList( s );
}

//--------------------------------------------------------------
/*
 * Prints a list of the items in the room.
 */
void Room::printItems( std::ostream & s ) const
{
    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        s << "\nThere is a " << iter->second->getName() << " on the floor.\n";
    }
    std::map<ID, Container *>::const_iterator iter2;
    for ( iter2 = m_containers.begin();
            iter2 != m_containers.end(); ++iter2 )
    {
        s << "\nThere is a " << iter2->second->getName() << " on the floor.\n";
    }
}

//--------------------------------------------------------------
/*
 * Saves a list of the items in the room in the form:
 *   count id ...
 */
void Room::saveItemList( std::ostream & s ) const
{
    s << ' ' << m_carryables.size() + m_containers.size();

    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        s << ' ' << iter->first;
    }
    std::map<ID, Container *>::const_iterator iter2;
    for ( iter2 = m_containers.begin();
            iter2 != m_containers.end(); ++iter2 )
    {
        s << ' ' << iter2->first;
    }
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Passage::clone() const
{
    return new Passage(*this);
}

//--------------------------------------------------------------
/*
 * Sets the exits from this room.
 */
void Passage::setExits( Adjacency * v )
{
    if ( v->getExitCount() != 2 )
    {
        std::cerr << "ERROR: Passage does not have exactly 2 exits.\n";
        std::exit( 1 );
    }
    else
    {
        Feature::setExits( v );
    }
}

//-------------------------------------------------------------
/*
 * Saves the feature to the specified stream.  Meant
 * for writing to disk.
 */
void Passage::save( std::ostream & s )
{
    Feature::save( s );
    s << "passage ";
    s << itemID << ' ' << name << ' ';
    description.save( s );

    saveItemList( s );
}

//-------------------------------------------------------------
/*
 * default constructor.  Sets initial state to closed.
 */
Door::Door()
{
    setState( LockStateFactory::generate("closed") );
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Door::clone() const
{
    return new Door(*this);
}

//-------------------------------------------------------------
/*
 * Returns true if this is a doorway and it is closed.
 */
bool Door::isClosed() const
{
    return m_state->isClosed();
}

//-------------------------------------------------------------
/*
 * Returns true if this is a doorway and it is open.
 */
bool Door::isOpen() const
{
    return m_state->isOpen();
}

//-------------------------------------------------------------
/*
 * Opens the door if this happens to be a doorway.
 * Returns false if this can't be done.
 */
bool Door::openDoor()
{
    return m_state->open(this);
}

//--------------------------------------------------------------
/*
 * Sets the exits from this room.
 */
void Door::setExits( Adjacency * v )
{
    if ( v->getExitCount() != 2 )
    {
        std::cerr << "ERROR: Door does not have exactly 2 exits.\n";
        std::exit( 1 );
    }
    else
    {
        Feature::setExits( v );
    }
}

//-------------------------------------------------------------
/*
 * Inputs the feature
 */
void Door::input( std::istream & s, Map * map )
{
    string stateTag;
    Item::input( s, map );

    s >> stateTag;
    setState( LockStateFactory::generate(stateTag) );
}

//-------------------------------------------------------------
/*
 * Outputs a detailed description of the feature.
 */
void Door::printDescription( std::ostream & s ) const
{
    Item::printDescription( s );
    s << "\nThe door is " << *m_state << ".\n";
}

//-------------------------------------------------------------
/*
 * Saves the feature to the specified stream.  Meant
 * for writing to disk.
 */
void Door::save( std::ostream & s )
{
    Feature::save( s );
    s << "doorway ";
    s << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << *m_state;
}

//-------------------------------------------------------------
/*
 * Gets the state of the door.
 */
LockState & Door::getState() const
{
    return *m_state;
}

//-------------------------------------------------------------
/*
 * Sets the state of the door: open or closed.
 */
void Door::setState( LockState * state )
{
    m_state = state;
}

//-------------------------------------------------------------
/*
 * default constructor.  Sets initial state to locked.
 */
LockableDoor::LockableDoor()
{
    setState( LockStateFactory::generate("locked") );
    m_lock = 0;
}

//-------------------------------------------------------------
/*
 * destructor
 */
LockableDoor::~LockableDoor()
{
    delete m_lock;
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * LockableDoor::clone() const
{
    return new LockableDoor(*this);
}

//-------------------------------------------------------------
/*
 * Returns true if this is a doorway and it is locked.
 */
bool LockableDoor::isLocked() const
{
    return getState().isLocked();
}

//-------------------------------------------------------------
/*
 * Unlocks the door with the given key if this happens
 * to be a doorway.  Returns false if this can't be
 * done.
 */
bool LockableDoor::unlockDoor( Key * key )
{
    return getState().unlock( this, key, m_lock );
}

//-------------------------------------------------------------
/*
 * Inputs the feature
 */
void LockableDoor::input( std::istream & s, Map * map )
{
    ID id;
    Door::input( s, map );
    s >> id;

    delete m_lock;
    m_lock = new Lock( id );
}

//-------------------------------------------------------------
/*
 * Saves the feature to the specified stream.  Meant
 * for writing to disk.
 */
void LockableDoor::save( std::ostream & s )
{
    Feature::save( s );
    s << "lockableDoorway ";
    s << itemID << ' ' << name << ' ';
    description.save( s );
    s << ' ' << getState() << ' ' << m_lock->getKeyID();
}

//--------------------------------------------------------------
/*
 * Copy constructor
 */
LockableDoor::LockableDoor( const LockableDoor & v )
{
    if ( v.m_lock == 0 )
    {
        m_lock = 0;
    }
    else
    {
        m_lock = new Lock( *v.m_lock );
    }
}

//--------------------------------------------------------------
/*
 * Assignment operator
 */
LockableDoor & LockableDoor::operator = ( const LockableDoor & v )
{
    if ( this != &v )
    {
        delete m_lock;

        if ( v.m_lock == 0 )
        {
            m_lock = 0;
        }
        else
        {
            m_lock = new Lock( *v.m_lock );
        }
    }

    return *this;
}

/* vim: set et sw=4 tw=65: */
