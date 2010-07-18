#ifndef STARTROOM_H
#define STARTROOM_H

/* StartRoom.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include <istream>
#include <ostream>

#include "ID.h"
#include "Item.h"

class Map;

/*
 * This class represents the start feature for the dungeon.
 */

class StartRoom : public Item
{
    public:
        virtual void addToMap( Map * map );
          // Adds this item to the map

        virtual Item * clone() const;
          // dynamic copy

        const ID & getLocationID() const;
          // Gets the location of the item

        virtual void input( std::istream & s, Map * );
          // Inputs the start room in format:
          //   featureId

        virtual void printDescription( std::ostream & s );
          // Outputs the start room in a human-readable format

        virtual void save( std::ostream & s );
          // Saves the start room to disk in same format input,
          // except adds type tag in front

    private:
        ID m_start;
          // The start feature
};

/* vim: set et sw=4 tw=65: */
#endif
