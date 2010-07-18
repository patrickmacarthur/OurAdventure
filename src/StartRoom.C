/* StartRoom.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include "StartRoom.h"

#include "Feature.h"
#include "Map.h"

/*
 * This class represents the start feature for the dungeon.
 */


//-------------------------------------------------------------
/*
 * Adds this item to the map
 */
void StartRoom::addToMap( Map * map )
{
    map->add( this );
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * StartRoom::clone() const
{
    return new StartRoom(*this);
}

//-------------------------------------------------------------
/*
 * Gets the location of the item
 */
const ID & StartRoom::getLocationID() const
{
    return m_start;
}

//-------------------------------------------------------------
/*
 * Inputs the start room in format:
 * featureId
 */
void StartRoom::input( std::istream & s, Map * map )
{
    s >> m_start;
}

//-------------------------------------------------------------
/*
 * Outputs the start room in a human-readable format
 */
void StartRoom::printDescription( std::ostream & s )
{
    s << "StartRoom: Description goes here.\n";
}

//-------------------------------------------------------------
/*
 * Saves the start room to disk in same format input,
 * except adds type tag in front
 */
void StartRoom::save( std::ostream & s )
{
    s << "start " << m_start;
}

/* vim: set et sw=4 tw=65: */
