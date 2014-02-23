/* Direction.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS516 Final Project
 */

#include "Direction.h"

/*
 * The Direction class stores the name of a particular direction.
 * It may be input or output.
 */

//-------------------------------------------------------------
/*
 * Default constructor
 */
Direction::Direction()
{
}

//-------------------------------------------------------------
/*
 * Constructs a direction with the given string
 */
Direction::Direction( const std::string & v ) : str(v)
{
}

//--------------------------------------------------------------
/*
 * Equality operators
 */
bool Direction::operator == ( const Direction & v ) const
{
    return str == v.str;
}

bool Direction::operator != ( const Direction & v ) const
{
    return str != v.str;
}

//--------------------------------------------------------------
/*
 * Relational operators
 */
bool Direction::operator < ( const Direction & v ) const
{
    return str < v.str;
}

bool Direction::operator <= ( const Direction & v ) const
{
    return str <= v.str;
}

bool Direction::operator > ( const Direction & v ) const
{
    return str > v.str;
}

bool Direction::operator >= ( const Direction & v ) const
{
    return str >= v.str;
}

//-------------------------------------------------------------
/*
 * Inputs the direction.
 */
std::istream & operator >> ( std::istream & s, Direction & v )
{
    v.input( s );
    return s;
}

void Direction::input( std::istream & s )
{
    s >> str;
}

//-------------------------------------------------------------
/*
 * Outputs the direction.
 */
std::ostream & operator << ( std::ostream & s, const Direction & v )
{
    v.output( s );
    return s;
}

void Direction::output( std::ostream & s ) const
{
    s << str;
}

/* vim: set et sw=4 tw=65: */
