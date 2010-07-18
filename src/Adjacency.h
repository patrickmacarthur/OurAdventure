#ifndef ADJACENCY_H
#define ADJACENCY_H

/* Adjacency.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include <istream>
#include <ostream>
#include <map>

#include "Direction.h"
#include "Item.h"

class Feature;
class Map;

/*
 * This class represents an adjacency between rooms.
 */

class Adjacency : public Item
{
    public:
        Adjacency();
          // constructor

        virtual ~Adjacency();
          // destructor

        virtual void addToMap( Map * map );
          // Adds this item to the map

        virtual Item * clone() const;
          // dynamic copy

        virtual Feature * getExit( const Direction & );
          // Gets the exit in the given direction.  Returns 0 if
          // there is no feature in that direction.

        virtual int getExitCount() const;
          // Returns the number of exits.

        const ID & getFeatureID() const;
          // Returns the ID of the "source" feature.

        virtual void input( std::istream & s, Map * );
          // Inputs the adjacency in the format:
          // featureId directionCount directionName featureId ...

        virtual void printDescription( std::ostream & s );
          // Outputs the adjacency list in a human-readable
          // format

        virtual void save( std::ostream & s );
          // Saves the adjacency list to disk in same format
          // input, except adds type tag in front

    private:
        std::map<Direction, Feature *> m_table;

        ID m_featureID;
};

/* vim: set et sw=4 tw=65: */
#endif
