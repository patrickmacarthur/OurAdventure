#ifndef FEATURE_H
#define FEATURE_H

/* Feature.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include <istream>
#include <ostream>
#include <list>
#include <map>

#include "Direction.h"
#include "Gold.h"
#include "ID.h"
#include "Item.h"

class Adjacency;
class Carryable;
class Container;
class Key;
class Lock;
class LockState;

/*
 * The Feature class represents a feature (room, passage, or
 * doorway) in the dungeon.  All features have exits that may be
 * queried for.  Some features may have items on the floor; these
 * may be taken (removed), queried, and more may be dropped
 * (added) if the feature allows items.  The feature and
 * adjacency list may be input and saved.
 */

class Feature : public Item
{
    public:
        Feature();
          // default constructor


        virtual ~Feature();
          // destructor

        virtual bool addItem( Carryable * );
          // Adds an item to the feature.  Returns false if the
          // item cannot be dropped in this feature for whatever
          // reason.

        virtual void addToMap( Map * map );
          // Adds this item to the map

        virtual Item * clone() const;
          // dynamic copy

        virtual Carryable * getCarryableItem( const Name & );
          // Returns the carryable item in the feature with the
          // given name.  If there is no carryable item in the
          // feature, return false.

        virtual Container * getContainer( const Name & );
          // Returns the container in the feature with the given
          // name.  If there is no container in the feature,
          // return false.

        Feature * getExit( const Direction & ) const;
          // Returns the exit from the given direction.  Returns
          // 0 if there is no feature in that direction.

        virtual std::list<Item *> getItems() const;
          // Returns a list of items in the feature.  If there
          // are no items, returns an empty list.

        virtual Gold getPoints() const;
          // Returns the total score of all items in this room.

        virtual bool hasItem( const Item * ) const;
          // Returns true if the item is in this feature

        virtual bool isClosed() const;
          // Returns true if this is a doorway and it is closed.

        virtual bool isLocked() const;
          // Returns true if this is a doorway and it is locked.

        virtual bool isOpen() const;
          // Returns true if this is not a doorway or it is open.

        virtual bool openDoor();
          // Opens the door if this happens to be a doorway.
          // Returns false if this can't be done.

        void setExits( Adjacency * );
          // Sets the exits from this room.

        virtual bool unlockDoor( Key * key );
          // Unlocks the door with the given key if this happens
          // to be a doorway.  Returns false if this can't be
          // done.

        virtual bool removeItem( const Carryable * );
          // Removes a carryable item from the feature.  Returns
          // false if the item cannot be removed from this
          // feature for whatever reason.

        virtual void save( std::ostream & s );
          // Saves the feature to the specified stream.  Meant
          // for writing to disk.

        virtual void saveExits( std::ostream & s );
          // Saves the exits to this feature to the specified
          // stream.  Meant for writing to disk.

    protected:
        Feature( const Feature & );
          // copy constructor

        Feature & operator = ( const Feature & );
          // assignment operator

    private:
        Adjacency * m_exits;
          // The exit table
};

/*
 * The Room class represents a room in the dungeon that can have
 * any number of exits and items on the floor.
 */

class Room : public Feature
{
    public:
        virtual ~Room();
          // destructor

        virtual bool addItem( Carryable * );
          // Adds an item to the feature.  Returns false if the
          // item cannot be dropped in this feature for whatever
          // reason.

        virtual Item * clone() const;
          // dynamic copy

        virtual std::list<Item *> getItems() const;
          // Returns a list of items in the feature.  If there
          // are no items, returns an empty list.

        virtual Carryable * getCarryableItem( const Name & );
          // Returns the carryable item in the feature with the
          // given name.  If there is no carryable item in the
          // feature, return false.

        virtual Container * getContainer( const Name & );
          // Returns the container in the feature with the given
          // name.  If there is no container in the feature,
          // return false.

        virtual Gold getPoints() const;
          // Returns the total score of all items in this room.

        virtual bool hasItem( const Item * ) const;
          // Returns true if the item is in this feature

        virtual void input( std::istream & s, Map * );
          // Inputs the feature

        virtual void printDescription( std::ostream & s ) const;
          // Outputs a detailed description of the feature and
          // all items within

        virtual bool removeItem( const Carryable * );
          // Removes a carryable item from the feature.  Returns
          // false if the item cannot be removed from this
          // feature for whatever reason.

        virtual void save( std::ostream & s );
          // Saves the feature to the specified stream.  Meant
          // for writing to disk.

    protected:
        void printItems( std::ostream & s ) const;
          // Prints a list of the items in the room.

        void saveItemList( std::ostream & s ) const;
          // Saves a list of the items in the room in the form:
          //   count id ...
    private:
        std::map<ID, Carryable *> m_carryables;
        std::map<ID, Container *> m_containers;
          // The collections of items within the feature
};

/*
 * The Passage class represents a room with only two exits that
 * can have items on the floor.
 */

class Passage : public Room
{
    public:
        virtual Item * clone() const;
          // dynamic copy

        void setExits( Adjacency * );
          // Sets the exits from this room.

        virtual void save( std::ostream & s );
          // Saves the feature to the specified stream.  Meant
          // for writing to disk.
};

/*
 * The Door class represents a doorway with an entranceway.  The
 * entranceway is in front of the door, and the door must be
 * opened prior to entering.  There may be no items in a doorway
 * entrance.
 */

class Door : public Feature
{
    public:
        Door();
          // default constructor.  Sets initial state to closed.

        virtual Item * clone() const;
          // dynamic copy

        virtual bool isClosed() const;
          // Returns true if this is a doorway and it is closed.

        virtual bool isOpen() const;
          // Returns true if this doorway is open.

        virtual bool openDoor();
          // Opens the door if this happens to be a doorway.
          // Returns false if this can't be done.

        void setExits( Adjacency * );
          // Sets the exits from this room.

        virtual void input( std::istream & s, Map * );
          // Inputs the feature

        virtual void printDescription( std::ostream & s ) const;
          // Outputs a detailed description of the feature.

        virtual void save( std::ostream & s );
          // Saves the feature to the specified stream.  Meant
          // for writing to disk.

    protected:
        friend class LockState;

        LockState & getState() const;
          // Gets the state of the door.

        void setState( LockState * state );
          // Sets the state of the door: open or closed.
    private:
        LockState * m_state;
          // State of the door: open or closed.  Initial state
          // will be closed.
};

/*
 * The LockableDoor class represents a locked door with an
 * entranceway.  The entranceway is in front of the door, and the
 * door must be unlocked with the appropriate key and opened
 * prior to entering.  There may be no items in a doorway
 * entrance.
 */

class LockableDoor : public Door
{
    public:
        LockableDoor();
          // default constructor.  Sets initial state to locked.

        virtual ~LockableDoor();
          // destructor

        virtual Item * clone() const;
          // dynamic copy

        virtual bool isLocked() const;
          // Returns true if this is a doorway and it is locked.

        virtual bool unlockDoor( Key * key );
          // Unlocks the door with the given key if this happens
          // to be a doorway.  Returns false if this can't be
          // done.

        virtual void input( std::istream & s, Map * );
          // Inputs the feature

        virtual void save( std::ostream & s );
          // Saves the feature to the specified stream.  Meant
          // for writing to disk.

    protected:
        LockableDoor( const LockableDoor & );
          // copy constructor

        LockableDoor & operator = ( const LockableDoor & );
          // assignment operator

    private:
        Lock * m_lock;
          // The lock on the door
};

/* vim: set et sw=4 tw=65: */
#endif
