#ifndef DIRECTIONLIST_H
#define DIRECTIONLIST_H

/* DirectionList.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS516 Final Project
 */

#include <istream>
#include <ostream>
#include <list>

#include "Item.h"

class Direction;
class Map;

/*
 * The DirectionList class contains a list of valid directions in
 * the cave.
 */

class DirectionList : public Item
{
    public:
        DirectionList();
          // default (no-argument) constructor

        DirectionList( const DirectionList & );
          // copy constructor

        DirectionList & operator = ( const DirectionList & );
          // assignment operator

        virtual ~DirectionList();
          // destructor

        virtual Item * clone() const;
          // dynamic copy

        virtual void addToMap( Map * map );
          // Adds this item to the map

        bool isValid( const Direction & direction ) const;
          // Returns true iff the given direction is valid

        virtual void input( std::istream & s, Map * map );
          // Inputs the initial direction list.  Takes a count
          // followed by the directions, space-delimited.

        virtual void printDescription( std::ostream & s ) const;
          // Outputs the initial direction list.  Outputs the
          // count followed by the names of the directions,
          // space-delimited.

        virtual void save( std::ostream & s );
          // Outputs the direction list in same format input.

    protected:
        void clear();
          // Clears the list, deleting all of the elements

    private:
        std::list<Direction *> m_directions;
};

/* vim: set et sw=4 tw=65: */
#endif
