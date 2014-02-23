/* Adjacency.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include "Adjacency.h"

#include "Feature.h"
#include "Map.h"

/*
 * The Adjacency class represents an adjacency between rooms.
 */

//--------------------------------------------------------------
/*
 * Constructor
 */
Adjacency::Adjacency()
{
}

//--------------------------------------------------------------
/*
 * Destructor
 */
Adjacency::~Adjacency()
{
}

//-------------------------------------------------------------
/*
 * Adds this item to the map
 */
void Adjacency::addToMap( Map * map )
{
    map->add( this );
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * Adjacency::clone() const
{
    return new Adjacency(*this);
}

//--------------------------------------------------------------
/*
 * Gets the exit in the given direction.  Returns 0 if there is
 * no feature in that direction.
 */
Feature * Adjacency::getExit( const Direction & v )
{
    std::map<Direction, Feature*>::iterator iter;
    iter = m_table.find( v );
    if ( iter == m_table.end() )
    {
        return 0;
    }
    else
    {
        return iter->second;
    }
}

//--------------------------------------------------------------
/*
 * Returns the number of exits.
 */
int Adjacency::getExitCount() const
{
    return m_table.size();
}

//--------------------------------------------------------------
/*
 * Returns the ID of the "source" feature.
 */
const ID & Adjacency::getFeatureID() const
{
    return m_featureID;
}

//-------------------------------------------------------------
/*
 * Inputs the adjacency in the format:
 * featureId directionCount directionName featureId ...
 */
void Adjacency::input( std::istream & s, Map * map )
{
    int count;
    Direction dir;
    ID id;

    s >> m_featureID;
    s >> count;

    for ( int i = 0; i < count; ++i )
    {
        s >> dir >> id;
        if ( map )
        {
            m_table[ dir ] = map->getFeature( id );
        }
    }
}

//-------------------------------------------------------------
/*
 * Outputs the adjacency list in a human-readable
 * format
 */
void Adjacency::printDescription( std::ostream & s )
{
    if ( m_table.empty() )
    {
        s << "(No exits)\n";
    }
    else
    {
        s << "(Exits are ";
        std::map<Direction, Feature*>::iterator iter;
        iter = m_table.begin();
        s << iter->first;
        ++iter;
        while ( iter != m_table.end() )
        {
            s << '/' << iter->first;
            ++iter;
        }
        s << ")\n";
    }
}

//-------------------------------------------------------------
/*
 * Saves the adjacency list to disk in same format
 * input, except adds type tag in front
 */
void Adjacency::save( std::ostream & s )
{
    s << "adj " << m_featureID << ' '
      << m_table.size() << ' ';

    std::map<Direction, Feature*>::iterator iter;
    for ( iter = m_table.begin(); iter != m_table.end(); ++iter )
    {
        s << iter->first << ' ' << iter->second->getID() << ' ';
    }
}

/* vim: set et sw=4 tw=65: */
