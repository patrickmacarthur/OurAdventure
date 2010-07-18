#ifndef MAP_H
#define MAP_H

/* Map.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include <istream>
#include <ostream>
#include <list>
#include <map>

#include "Gold.h"
#include "ID.h"

class Adjacency;
class Carryable;
class Container;
class DirectionList;
class Feature;
class Item;
class ItemFactory;
class Name;
class StartRoom;

/*
 * The Map class contains the map of the cave that the user is
 * currently in.
 *
 * The map is read in from (and saved to) data files in the
 * following format:
 *  # Comment; ignored
 *  directions num string string ...
 *  consumable id shortName |long descr| healthValue weight size
 *  key id shortName |long descr|
 *  treasure id shortName |long descr| points weight size
 *  pack id shortName |long descr| weight capacity
 *  container box id shortName |long descr| state itemList
 *  container chestid shortName |long descr| state itemList keyId
 *  feature room id shortName |long descr| itemList
 *  feature passage id shortName |long descr| itemList
 *  feature lockableDoorway id shortName |long descr| state keyId
 *  feature doorway id shortName |long descr| state
 *  adj id numAdj dir id dir id ...
 *  start id
 * Items MUST be specified before features.  Directions and
 * features MUST be specified before adjacencies.  itemList is
 * specified as follows:
 *  numItems id ...
 * state may be one of the following: locked (for chests and
 * lockable doors only), closed, or open.
 *
 * Any map that does not conform to the above specifications will
 * be rejected, and the program will terminate with a suitable
 * error message.
 */

class Map
{
    public:
        explicit Map( ItemFactory * factory );
          // Constructs a map.  Expects an ItemFactory that has
          // already been loaded with all appropriate items.
          // The map will take ownership of the ItemFactory.

        ~Map();
          // destructor

        void clear();
          // removes all items from the map

        const DirectionList & getDirections() const;
          // Gets the list of directions in this cave.

        Feature * getFeature( const ID & id );
          // Gets the feature with the given id.  Returns 0 if
          // there is no feature with that id.

        Carryable * getCarryableItem( const ID & id );
          // Gets the carryable item with the given id.  Returns
          // 0 if there is no item with that id, or it is not
          // carryable.

        Container * getContainer( const ID & id );
          // Gets the container with the given id.  Returns
          // 0 if there is no item with that id, or it is not
          // a container.

        const ID * getItemId( const Feature &, const Name & ) const;
          // Gets the id of the item with the given name in the
          // given room.  Returns 0 if there is no item with that
          // id.

        std::map<Name, const Item *> getItemLocations();
          // Returns list of all items, ordered by name.

        Gold getPoints() const;
          // Returns the total score of all items in the cave.

        Feature * getStartRoom();
          // Returns a pointer to the start feature.

        void input( std::istream & s );
          // Inputs the map from disk, in format above

        void output( std::ostream & s );
          // Outputs the map in a human-readable format

        void save( std::ostream & s );
          // Saves the map to disk in same format input

    //protected: //(should be protected, but don't want to make
    //all these classes friends)
        void add( Carryable * item );
        void add( Container * item );
        void add( DirectionList * item );
        void add( Feature * item );
        void add( Adjacency * item );
        void add( StartRoom * item );
          // Adds an item to the map.  This function is
          // overloaded to handle all different types of items,
          // and is only menat to be called from
          // Item::addToMap().  This function is given the map to
          // insert into; and fakes multiple-dispatch such that
          // the correct add() method here gets called.

    private:
        DirectionList * m_dirList;
          // List of valid directions in the adventure

        std::map<ID, Carryable *> m_carryables;
          // Table of all items in the dungeon, indexed by Id

        std::map<ID, Container *> m_containers;
          // Table of all items in the dungeon, indexed by Id

        std::map<ID, Feature *> m_features;
          // Table of all features in the dungeon, indexed by Id

        StartRoom * m_startRoom;
          // The start room for the adventure

        ItemFactory * m_itemFactory;
          // The item factory used to generate all input items.
};

/* vim: set et sw=4 tw=65: */
#endif
