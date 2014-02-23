/* DirectionList.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS516 Final Project
 */

#include "DirectionList.h"
#include "Direction.h"
#include "Map.h"

/*
 * The DirectionList class contains a list of valid directions in
 * the cave.
 */

//--------------------------------------------------------------
/*
 * Default (no-argument) constructor
 */
DirectionList::DirectionList()
{
}

//-------------------------------------------------------------
/*
 * destructor
 */
DirectionList::~DirectionList()
{
    this->clear();
}

//-------------------------------------------------------------
/*
 * dynamic copy
 */
Item * DirectionList::clone() const
{
    return new DirectionList(*this);
}

//-------------------------------------------------------------
/*
 * Adds this item to the map
 */
void DirectionList::addToMap( Map * map )
{
    map->add( this );
}

//-------------------------------------------------------------
/*
 * Returns true iff the given direction is valid
 */
bool DirectionList::isValid( const Direction & direction ) const
{
    std::list<Direction *>::const_iterator iter;
    for ( iter = m_directions.begin(); iter != m_directions.end();
            ++iter )
    {
        if ( direction == **iter )
        {
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------
/*
 * Inputs the initial direction list.  Takes a count
 * followed by the directions, space-delimited.
 */
void DirectionList::input( std::istream & s, Map * map )
{
    int count;

    // Clear the list of any previous garbage
    this->clear();

    // Input new stuff
    s >> count;
    for ( int i = 0; i < count; ++i )
    {
        Direction *dir = new Direction;
        s >> *dir;
        m_directions.push_back( dir );
    }
}

//-------------------------------------------------------------
/*
 * Outputs the initial direction list.  Outputs the
 * count followed by the names of the directions,
 * space-delimited.
 */
void DirectionList::printDescription( std::ostream & s ) const
{
    s << "Available directions: ";

    std::list<Direction *>::const_iterator iter;
    iter = m_directions.begin();
    s << **iter;
    ++iter;
    while ( iter != m_directions.end() )
    {
        s << ", " << **iter;
        ++iter;
    }
    s << '\n';
}

//-------------------------------------------------------------
/*
 * Outputs the direction list in same format input.
 */
void DirectionList::save( std::ostream & s )
{
    s << "directions " << m_directions.size() << ' ';

    std::list<Direction *>::iterator iter;
    for ( iter = m_directions.begin(); iter != m_directions.end();
            ++iter )
    {
        s << **iter << ' ';
    }
    s << '\n';
}

//--------------------------------------------------------------
/*
 * Clears the list, deleting all of the elements.
 */
void DirectionList::clear()
{
    std::list<Direction *>::iterator iter;
    for ( iter = m_directions.begin(); iter != m_directions.end();
            ++iter )
    {
        delete *iter;
    }
    m_directions.clear();
}

//--------------------------------------------------------------
/*
 * Copy constructor
 */
DirectionList::DirectionList( const DirectionList & v )
{
    std::list<Direction *>::const_iterator iter;
    for ( iter = v.m_directions.begin();
            iter != v.m_directions.end();
            ++iter )
    {
        m_directions.push_back( new Direction( **iter ) );
    }
}

//--------------------------------------------------------------
/*
 * Assignment operator
 */
DirectionList & DirectionList::operator = ( const DirectionList & v )
{
    if ( this != &v )
    {
        this->clear();

        std::list<Direction *>::const_iterator iter;
        for ( iter = v.m_directions.begin();
              iter != v.m_directions.end();
              ++iter )
        {
            m_directions.push_back( new Direction( **iter ) );
        }
    }

    return *this;
}

/* vim: set et sw=4 tw=65: */
