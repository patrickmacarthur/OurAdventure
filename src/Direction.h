#ifndef DIRECTION_H
#define DIRECTION_H

/* Direction.h
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS516 Final Project
 */

#include <istream>
#include <ostream>
#include <string>

/*
 * The Direction class stores the name of a particular direction.
 * It may be input or output.
 */

class Direction
{
    public:
        Direction();
          // Default constructor

        explicit Direction( const std::string & v );
          // Constructs a direction with the given string

        bool operator == ( const Direction & ) const;
        bool operator != ( const Direction & ) const;
          // Equality operators

        bool operator < ( const Direction & ) const;
        bool operator <= ( const Direction & ) const;
        bool operator > ( const Direction & ) const;
        bool operator >= ( const Direction & ) const;
          // Relational operators.

        void input( std::istream & s );
          // Inputs the direction.

        void output( std::ostream & s ) const;
          // Outputs the direction.

    private:
        std::string str;
};

std::istream & operator >> ( std::istream & s, Direction & v );
  // Input operator; provided for convenience.  Calls v->input()

std::ostream & operator << ( std::ostream & s, const Direction & v );
  // Output operator; provided for convenience.  Calls
  // v->output()

/* vim: set et sw=4 tw=65: */
#endif
